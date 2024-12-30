#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterRow.generated.h"

USTRUCT(BlueprintType)
struct FCharacterRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName NameID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D>  Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int HP = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Attack = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Defense = 1;
	FCharacterRow() : HP(0) , Attack(0) , Defense(0) { }
};