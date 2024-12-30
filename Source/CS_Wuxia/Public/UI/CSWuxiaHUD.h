// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CSWuxiaHUD.generated.h"

class UMVVM_ViewModelBase;
/**
 * 
 */
UCLASS(Abstract)
class CS_WUXIA_API ACSWuxiaHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "ACSWuxiaHUD")
	TSubclassOf<UMVVM_ViewModelBase> ViewModelBaseClass;

	UPROPERTY(BlueprintReadOnly, Category = "ACSWuxiaHUD")
	TObjectPtr<UMVVM_ViewModelBase> ViewModelBase;


	
	
protected:
	virtual void BeginPlay() override;
	
};
