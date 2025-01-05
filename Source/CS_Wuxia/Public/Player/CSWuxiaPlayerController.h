// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CSWuxiaPlayerController.generated.h"

class UMainProfileWidget;
class UShowNameWidget;
class USplineComponent;
class UNiagaraSystem;
struct FGameplayTag;
class UCSWuxiaInputConfig;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

enum class ETargetingStatus : uint8
{
	TargetingEnemy,
	TargetingNonEnemy,
	NotTargeting
};


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
	UPROPERTY(EditDefaultsOnly,Category="Input")
	FVector2D OffsetMousePosition;
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
	
	UPROPERTY(EditAnywhere,Category="UI")
	TObjectPtr<UShowNameWidget> ShowNameWidget;
	UPROPERTY(EditAnywhere,Category="UI")
	TObjectPtr<UMainProfileWidget> MainProfileWidget;

	void InputTagPressed(const FGameplayTag InputTag);
	void InputTagReleased(const FGameplayTag InputTag);
	void InputTagHeld(const FGameplayTag InputTag);

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	TObjectPtr<AActor> LastActor;
	TObjectPtr<AActor> ThisActor;
	FHitResult CursorHit;
	static void HightlightActor(AActor* Actor);
	static void UnHightlightActor(AActor* Actor);
	void ShowActorDisplayName() const;

	/*  click auto move */
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.0f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	ETargetingStatus TargetingStatus =ETargetingStatus::NotTargeting;
	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.0f;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ClickEffect;
	
	void AutoRun();
	/*  click auto move */
};


