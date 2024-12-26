// Copyright CS_WUXIA 


#include "Player/CSWuxiaPlayerController.h"

#include "CSWuxiaGameplayTags.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SplineComponent.h"
#include "Input/CSWuxiaInputComponent.h"
#include "Interface/HightlightInterface.h"

class UNavigationPath;

ACSWuxiaPlayerController::ACSWuxiaPlayerController()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}
void ACSWuxiaPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
}
void ACSWuxiaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick( DeltaTime );
	CursorTrace();
	AutoRun();
}



void ACSWuxiaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputLocalPlayerSubsystem* EnhanceInputSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>( GetLocalPlayer() );
	if (EnhanceInputSubsystem)
	{
		EnhanceInputSubsystem->AddMappingContext(InputContext,0);
	}
	UCSWuxiaInputComponent* CSWuxiaInputComponent = CastChecked<UCSWuxiaInputComponent>(InputComponent);
	CSWuxiaInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ACSWuxiaPlayerController::Move);
	CSWuxiaInputComponent->BindAbilityActions(InputConfig,this,&ACSWuxiaPlayerController::InputTagPressed,&ACSWuxiaPlayerController::InputTagReleased,&ACSWuxiaPlayerController::InputTagHeld);
}

void ACSWuxiaPlayerController::InputTagPressed(const FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FCSWuxiaGameplayTags::Get().InputTag_LMB))
	{
		if (IsValid(ThisActor))
		{
			TargetingStatus = /*ThisActor->Implements<UEnemyInterface>() ? ETargetingStatus::TargetingEnemy : */ETargetingStatus::TargetingNonEnemy;
		}else
		{
			TargetingStatus = ETargetingStatus::NotTargeting;
		}
	}

	bAutoRunning = false;
}

void ACSWuxiaPlayerController::InputTagReleased(const FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FCSWuxiaGameplayTags::Get().InputTag_LMB))
	{
		return;
	}
	if(TargetingStatus != ETargetingStatus::TargetingEnemy /*&& !bShiftKeyDown*/)
	{
		if(const APawn* ControllerPawn = GetPawn<APawn>(); FollowTime<= ShortPressThreshold && ControllerPawn)
		{
			if(IsValid( ThisActor ) && ThisActor->Implements<UHightlightInterface>())
			{
				FVector OutLocation = FVector::ZeroVector;
				IHightlightInterface::Execute_MoveToLocation(ThisActor,OutLocation);
				CachedDestination = OutLocation;
			}
			else if(ClickEffect/* && ( GetAuraAbilitySystemComponent() && !GetAuraAbilitySystemComponent()->HasMatchingGameplayTag( FAuraGameplayTags::Get().Player_Block_InputPressed))*/)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ClickEffect, CachedDestination);
			}else
			{
				if (CursorHit.bBlockingHit)
				{
					CachedDestination = CursorHit.Location;
				}
			}
			
			if(const UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
				this, ControllerPawn->GetActorLocation(), CachedDestination))
			{
				TArray<FVector> Paths = NavPath->PathPoints;
				SplineComponent ->ClearSplinePoints();
				for (const FVector& Point : Paths)
				{
					SplineComponent->AddSplinePoint(Point,ESplineCoordinateSpace::World);
				}
				if(Paths.Num()>0)
				{
					CachedDestination = Paths.Last();
					bAutoRunning = true;
				}
			}
		}
	}
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("FollowTime: %f"), FollowTime));
	FollowTime = 0.0f;
	TargetingStatus = ETargetingStatus:: NotTargeting;
}

void ACSWuxiaPlayerController::InputTagHeld(const FGameplayTag InputTag)
{
}

void ACSWuxiaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0,Rotation.Yaw,0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
	if (APawn* const OwnerPawn = GetPawn())
	{
		OwnerPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
		OwnerPawn->AddMovementInput(RightDirection,InputAxisVector.X);
	}
}

void ACSWuxiaPlayerController::CursorTrace()
{
	const ECollisionChannel TraceChannel = /*IsValid( MagicCircle ) ? ECC_ExcludePlayers :*/ ECC_Visibility;
	GetHitResultUnderCursor(TraceChannel, false, CursorHit);
	if (!CursorHit.bBlockingHit)return;
	LastActor = ThisActor;
	if (CursorHit.GetActor() == GetPawn())
	{
		ThisActor = nullptr;
	}else if(IsValid(CursorHit.GetActor())&& CursorHit.GetActor()->Implements<UHightlightInterface>())
	{
		ThisActor = CursorHit.GetActor();
	}
	else
	{
		ThisActor = nullptr;
	}

	if (LastActor != ThisActor)
	{
		UnHightlightActor(LastActor);
		HightlightActor(ThisActor);
	}
}

void ACSWuxiaPlayerController::HightlightActor(AActor* Actor)
{
	if(IsValid(Actor)&& Actor->Implements<UHightlightInterface>())
	{
		IHightlightInterface::Execute_HighlightActor(Actor);
	}
}
void ACSWuxiaPlayerController::UnHightlightActor(AActor* Actor)
{
	if(IsValid(Actor)&& Actor->Implements<UHightlightInterface>())
	{
		IHightlightInterface::Execute_UnHighlightActor(Actor);
	}
}

void ACSWuxiaPlayerController::AutoRun()
{
	if (!bAutoRunning)return;
	if(APawn* ControllerPawn = GetPawn<APawn>())
	{
		const FVector LocationOnSpline = SplineComponent->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = SplineComponent->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControllerPawn->AddMovementInput(Direction);
		const float DistanceToDestination = (LocationOnSpline-CachedDestination).Length();
		if( DistanceToDestination < AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

