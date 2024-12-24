// Fill out your copyright notice in the Description page of Project Settings.


#include "CS_Wuxia/Public/Pawn/PlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/CSWuxiaInputComponent.h"
#include "Player/CSWuxiaPlayerController.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom , USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	FloatingPawnMovement->UpdatedComponent = RootComponent;
	
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	if ( ACSWuxiaPlayerController* PlayerController = Cast<ACSWuxiaPlayerController>( GetController() ) )
	{
		PlayerController->bShowMouseCursor = true;
	}
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );
	UCSWuxiaInputComponent* CSWuxiaInputComponent = CastChecked<UCSWuxiaInputComponent>(InputComponent);
	CSWuxiaInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&APlayerPawn::Move);
	CSWuxiaInputComponent->BindAction(ZoomAction,ETriggerEvent::Triggered,this,&APlayerPawn::Zoom);
	CSWuxiaInputComponent->BindAction(RotateCameraAction,ETriggerEvent::Triggered,this,&APlayerPawn::RotateCamera);
}



void APlayerPawn::Zoom(const FInputActionValue& InputActionValue)
{
	check(CameraBoom);
	const float Value = InputActionValue.Get<float>() * ZoomSpeed;
	const float Sec = GetWorld()->GetDeltaSeconds() * 10;
	ZoomRate = FMath::Lerp( Value, ZoomRate, Sec);
	CameraBoom->TargetArmLength += ZoomRate;
	CameraBoom->TargetArmLength = FMath::Clamp(CameraBoom->TargetArmLength,MinZoom,MaxZoom);
}

void APlayerPawn::RotateCamera(const FInputActionValue& InputActionValue)
{
	check(CameraBoom);
	const float Value = InputActionValue.Get<float>() * RotationSpeed;
	const float Sec = GetWorld()->GetDeltaSeconds() * 5;
	ZoomRate = FMath::Lerp( Value, ZoomRate, Sec);
	FRotator NewRotation = CameraBoom->GetComponentRotation();
	NewRotation.Yaw+= ZoomRate;
	CameraBoom->SetRelativeRotation( NewRotation );
	
}

void APlayerPawn::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0,Rotation.Yaw,0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection,InputAxisVector.Y);
	AddMovementInput(RightDirection,InputAxisVector.X);
}


