// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Interface/HightlightInterface.h"
#include "Interface/InteractableInterface.h"
#include "CSWuxiaCharacterBase.generated.h"

class UAttributeSet;
struct FCharacterRow;
class UWidgetComponent;

UCLASS()
class CS_WUXIA_API ACSWuxiaCharacterBase : public ACharacter ,public IAbilitySystemInterface, public IHightlightInterface  , public IInteractableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSWuxiaCharacterBase();
	UPROPERTY(EditAnywhere,BlueprintReadOnly , Category = "CharacterRowID")
	FName CharacterRowID ;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	FCharacterRow* GetCharacterRow() const { return CharacterRow; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	TObjectPtr<UMaterialInstanceDynamic> DynamicOutlineMaterialInstance;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Highlight")
	TObjectPtr<UMaterialInterface> OutlineMaterialInterface;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	TObjectPtr<UWidgetComponent> InteractableWidget;
	
	FCharacterRow* CharacterRow;


	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>  AbilitySystemComponent;
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*  IHightlightInterface  */
	UFUNCTION(BlueprintPure)
	virtual UMaterialInstanceDynamic* GetOutlineMaterialInstance() override;
	virtual	void HighlightActor_Implementation() override;
	virtual void UnHighlightActor_Implementation() override;
	virtual void MoveToLocation_Implementation(FVector& OutLocation) override;
	virtual FName GetActorName_Implementation() override;
	/*  IHightlightInterface  */


	/*  IInteractableInterface  */

	virtual void ShowInteractionWidget_Implementation() override;
	virtual void HideInteractionWidget_Implementation() override;
	/* IInteractableInterface */

	
	
	
private:

	// 顯示互動名稱
	FName DisplayName;

};

