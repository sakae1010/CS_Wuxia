// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class CS_WUXIA_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent , BlueprintCallable)
	void BlueprintInitializeWidgets();
};
