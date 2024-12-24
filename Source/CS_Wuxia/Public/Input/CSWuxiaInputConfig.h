// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CSWuxiaInputConfig.generated.h"



class UInputAction;
struct FGameplayTag;
USTRUCT(BlueprintType)
struct FCSWuxiaInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class CS_WUXIA_API UCSWuxiaInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	const UInputAction* GetAbilityInputActionForTag(const FGameplayTag& InputTag , bool bLogNotFound) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCSWuxiaInputAction> InputActions;
};
