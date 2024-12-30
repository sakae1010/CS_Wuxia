// Copyright CS_WUXIA 


#include "CSWuxiaGameplayTags.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

FCSWuxiaGameplayTags FCSWuxiaGameplayTags::GameplayTags;

void FCSWuxiaGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.InputTag_LMB = GameplayTagsManager.AddNativeGameplayTag(
	FName("InputTag.LMB"),
	FString("Left Mouse Button"));
	
	GameplayTags.InputTag_RMB = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Right Mouse Button"));
	

	GameplayTags.InputTag_1 = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("1 Key"));

	GameplayTags.InputTag_2 = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("2 Key"));

	GameplayTags.InputTag_3	= GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("3 Key"));

	GameplayTags.InputTag_4 = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("4 Key"));
	GameplayTags.InputTag_5 = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.5"),
		FString("5 Key"));
	GameplayTags.InputTag_6 = GameplayTagsManager.AddNativeGameplayTag(
		FName("InputTag.6"),
		FString("6 Key"));

	
	GameplayTags.Attribute_Base_Attack = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attribute.Base.Attack"),
		FString("Attack"));
	GameplayTags.Attribute_Base_Health = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attribute.Base.Health"),
		FString("Health"));
	GameplayTags.Attribute_Base_MaxHealth = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attribute.Base.MaxHealth"),
		FString("MaxHealth"));
	GameplayTags.Attribute_Base_ActionPoint = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attribute.Base.ActionPoint"),
		FString("ActionPoint"));
	GameplayTags.Attribute_Base_MaxActionPoint = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attribute.Base.MaxActionPoint"),
		FString("MaxActionPoint"));
	GameplayTags.Attribute_Base_Defense = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attribute.Base.Defense"),
		FString("Defense"));
	GameplayTags.Attribute_Base_DistancePerAP = GameplayTagsManager.AddNativeGameplayTag(
		FName("Attribute.Base.DistancePerAP"),
		FString("DistancePerAP"));
	
}
