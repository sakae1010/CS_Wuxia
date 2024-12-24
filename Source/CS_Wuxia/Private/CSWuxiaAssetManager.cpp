// Copyright CS_WUXIA 


#include "CSWuxiaAssetManager.h"
#include "AbilitySystemGlobals.h"
#include "CSWuxiaGameplayTags.h"

const UCSWuxiaAssetManager& UCSWuxiaAssetManager::Get()
{
	check(GEngine)
	return *Cast<UCSWuxiaAssetManager>(GEngine->AssetManager);
}

void UCSWuxiaAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FCSWuxiaGameplayTags::InitializeNativeGameplayTags();
	//UAbilitySystemGlobals 啟用
	UAbilitySystemGlobals::Get().InitGlobalData();
}
