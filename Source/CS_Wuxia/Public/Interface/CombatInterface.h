// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CS_WUXIA_API ICombatInterface
{
	GENERATED_BODY()

	
public:

	//戰鬥介面
	UFUNCTION(BlueprintNativeEvent)
	int32 GetPlayerLevel();
	
};
