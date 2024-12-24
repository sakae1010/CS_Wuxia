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

	
	// GameplayTags.InputTag_Passive_1 = GameplayTagsManager.AddNativeGameplayTag(
	// 	FName("InputTag.Passive.1"),
	// 	FString("Input Tag Passive 1 Ability"));
	//
	// GameplayTags.InputTag_Passive_2 = GameplayTagsManager.AddNativeGameplayTag(
	// 	FName("InputTag.Passive.2"),
	// 	FString("Input Tag Passive 2 Ability"));
	
}
