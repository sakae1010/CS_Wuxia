// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CS_WUXIA_API IInteractableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//顯示或隱藏互動 UI
	
	UFUNCTION(BlueprintNativeEvent)
	void ShowInteractionWidget(); 

	UFUNCTION(BlueprintNativeEvent)
	void HideInteractionWidget() ;
};
