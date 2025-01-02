// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CSWuxiaGameInstance.generated.h"

class ADataManager;
/**
 * 
 */
UCLASS()
class CS_WUXIA_API UCSWuxiaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UCSWuxiaGameInstance();
	FName GetStringTable(const FName& TableId, const FString& RowId) const;

public:
	UPROPERTY(EditDefaultsOnly, Category = "StringTable")
	TArray<TObjectPtr<UStringTable>> StringTables;

private:

};
