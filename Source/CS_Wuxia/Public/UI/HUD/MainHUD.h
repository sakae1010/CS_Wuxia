// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UMainWidget;
class UMainViewModel;
/**
 * 
 */
UCLASS()
class CS_WUXIA_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "AMainHUD")
	TSubclassOf<UMainViewModel> ViewModelClass;

	UPROPERTY(BlueprintReadOnly, Category = "AMainHUD")
	TObjectPtr<UMainViewModel> ViewModel;

	UPROPERTY(EditDefaultsOnly, Category = "AMainHUD")
	TSubclassOf<UUserWidget> MainWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "AMainHUD")
	TObjectPtr<UMainWidget> MainWidget;

protected:
	virtual void BeginPlay() override;
	
};
