// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CSWuxiaAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class CS_WUXIA_API UCSWuxiaAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static const UCSWuxiaAssetManager& Get() ;

protected:
	virtual void StartInitialLoading() override;
	
};
