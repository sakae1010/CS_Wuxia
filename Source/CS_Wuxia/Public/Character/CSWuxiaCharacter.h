// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "Character/CSWuxiaCharacterBase.h"
#include "CSWuxiaCharacter.generated.h"

class UBoxComponent;
class USphereComponent;
class UWidgetComponent;
class USpringArmComponent;
class UCameraComponent;
struct FInputActionValue;
class UInputAction;
/**
 * 
 */
UCLASS()
class CS_WUXIA_API ACSWuxiaCharacter : public ACSWuxiaCharacterBase 
{
	GENERATED_BODY()

public:	
	ACSWuxiaCharacter();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	TObjectPtr<USphereComponent>  InteractionSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	TObjectPtr<UBoxComponent> InteractionBox;
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
							  AActor* OtherActor,
							  UPrimitiveComponent* OtherComp,
							  int32 OtherBodyIndex,
							  bool bFromSweep,
							  const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent,
							AActor* OtherActor,
							UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex);


	UPROPERTY(EditAnywhere)
	bool IsUseSphere = true;


	UPROPERTY(EditAnywhere)
	float TraceDistance = 200.f;
	
	void InteractActor(AActor* Actor);
	void UnInteractActor(AActor* Actor);
};

