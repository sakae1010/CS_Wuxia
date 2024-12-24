// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawn.generated.h"

struct FInputActionValue;
class UInputAction;
class UFloatingPawnMovement;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CS_WUXIA_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> ZoomAction;

	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> RotateCameraAction;
	
	UPROPERTY(EditAnywhere,Category="Camera")
	float ZoomSpeed = 100.f;

	UPROPERTY(EditAnywhere,Category="Camera")
	float MaxZoom = 10000.f;

	UPROPERTY(EditAnywhere,Category="Camera")
	float MinZoom = 200.f;

	UPROPERTY(EditAnywhere,Category="Camera")
	float RotationSpeed = 0.3f;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;


	void Zoom(const FInputActionValue& InputActionValue);
	void RotateCamera(const FInputActionValue& InputActionValue);
	void Move(const FInputActionValue& InputActionValue);


	float ZoomRate = 0;
	float RotateCameraRate = 0;
	
};

