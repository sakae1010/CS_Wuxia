// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "Character/CSWuxiaCharacterBase.h"
#include "CSWuxiaCharacter.generated.h"

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


private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
};
