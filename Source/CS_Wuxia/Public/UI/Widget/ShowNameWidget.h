// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/CSWuxiaUserWidget.h"
#include "ShowNameWidget.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNameChanged,FText, NewName);
/**
 * 
 */
UCLASS()
class CS_WUXIA_API UShowNameWidget : public UCSWuxiaUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetOffsetMousePosition(const FVector2D& InPosition);
	UFUNCTION()
	void SetNameText(const FText& InName);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnNameChanged OnNameChangedEvent;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


public:
	
protected:
private:
	UPROPERTY()
	FVector2D OffsetMousePosition;

};
