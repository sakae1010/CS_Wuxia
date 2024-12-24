// Copyright CS_WUXIA 


#include "Player/CSWuxiaPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/CSWuxiaInputComponent.h"

ACSWuxiaPlayerController::ACSWuxiaPlayerController()
{
}

void ACSWuxiaPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick( DeltaTime );
}

void ACSWuxiaPlayerController::BeginPlay()
{
	Super::BeginPlay();
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
	// CSWuxiaInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ACSWuxiaPlayerController::Move);
	CSWuxiaInputComponent->BindAbilityActions(InputConfig,this,&ACSWuxiaPlayerController::InputTagPressed,&ACSWuxiaPlayerController::InputTagReleased,&ACSWuxiaPlayerController::InputTagHeld);
}

void ACSWuxiaPlayerController::InputTagPressed(const FGameplayTag InputTag)
{
}

void ACSWuxiaPlayerController::InputTagReleased(const FGameplayTag InputTag)
{
}

void ACSWuxiaPlayerController::InputTagHeld(const FGameplayTag InputTag)
{
}


// void ACSWuxiaPlayerController::Move(const FInputActionValue& InputActionValue)
// {
// 	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
// 	const FRotator Rotation = GetControlRotation();
// 	const FRotator YawRotation(0,Rotation.Yaw,0);
// 	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
// 	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
// 	auto OwnerPawn = GetPawn();
// 	if (!OwnerPawn) return;
// 	OwnerPawn->AddMovementInput(ForwardDirection,InputAxisVector.Y);
// 	OwnerPawn->AddMovementInput(RightDirection,InputAxisVector.X);
// }
