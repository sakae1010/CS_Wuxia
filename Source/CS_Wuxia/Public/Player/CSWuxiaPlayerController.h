// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CSWuxiaPlayerController.generated.h"

struct FGameplayTag;
class UCSWuxiaInputConfig;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class CS_WUXIA_API ACSWuxiaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACSWuxiaPlayerController();
	
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;


private:

	UPROPERTY(EditDefaultsOnly,Category="Input")
	TObjectPtr<UCSWuxiaInputConfig> InputConfig;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputMappingContext> InputContext;
	
	UPROPERTY(EditAnywhere,Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void InputTagPressed(const FGameplayTag InputTag);
	void InputTagReleased(const FGameplayTag InputTag);
	void InputTagHeld(const FGameplayTag InputTag);

	// void Move(const FInputActionValue& InputActionValue);
};


