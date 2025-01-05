// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/CSWuxiaUserWidget.h"
#include "MainProfileWidget.generated.h"

USTRUCT(BlueprintType)
struct FProfileData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly)
	FName Name;
	UPROPERTY(BlueprintReadOnly)
	int32 Level;
	UPROPERTY(BlueprintReadOnly)
	int32 Hp;
	UPROPERTY(BlueprintReadOnly)
	int32 MaxHp;
	// buff list
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShowProfile,FProfileData, ProfileData);
/**
 * 
 */
UCLASS()
class CS_WUXIA_API UMainProfileWidget : public UCSWuxiaUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnShowProfile OnShowProfileDelegate;


	void ShowActorProfile(const FProfileData& ProfileData) const;
	
};
