// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 * 
 */
struct FCSWuxiaGameplayTags
{
public:
	static const FCSWuxiaGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
	
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_5;
	FGameplayTag InputTag_6;

	/* 基礎屬性 測試用版本*/
	FGameplayTag Attribute_Base_Attack;
	FGameplayTag Attribute_Base_Health;
	FGameplayTag Attribute_Base_MaxHealth;
	FGameplayTag Attribute_Base_ActionPoint;
	FGameplayTag Attribute_Base_MaxActionPoint;
	FGameplayTag Attribute_Base_Defense;
	FGameplayTag Attribute_Base_DistancePerAP;
	
	 

	
	
private :
	static FCSWuxiaGameplayTags GameplayTags;
	
};
