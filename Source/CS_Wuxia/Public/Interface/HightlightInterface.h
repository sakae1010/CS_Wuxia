// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HightlightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UHightlightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CS_WUXIA_API IHightlightInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual UMaterialInterface* GetOutlineMaterialInstance();

	float GetHightlightDuration();
	
	UFUNCTION(BlueprintNativeEvent)
	void HighlightActor() ;
	
	UFUNCTION(BlueprintNativeEvent)
	void UnHighlightActor();

	UFUNCTION(BlueprintNativeEvent)
	void MoveToLocation(FVector& OutLocation);
	
};
