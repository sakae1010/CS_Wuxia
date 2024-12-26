// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HightlightInterface.h"
#include "CSWuxiaCharacterBase.generated.h"

class UWidgetComponent;

UCLASS()
class CS_WUXIA_API ACSWuxiaCharacterBase : public ACharacter , public IHightlightInterface 
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACSWuxiaCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TObjectPtr<UMaterialInstanceDynamic> DynamicOutlineMaterialInstance;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Highlight")
	TObjectPtr<UMaterialInterface> OutlineMaterialInterface;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	UWidgetComponent* InteractableWidget;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*  IHightlightInterface  */
	virtual float GetHightlightDuration() const;
	UFUNCTION(BlueprintPure)
	virtual UMaterialInstanceDynamic* GetOutlineMaterialInstance() override;
	virtual	void HighlightActor_Implementation() override;
	virtual void UnHighlightActor_Implementation() override;
	virtual void MoveToLocation_Implementation(FVector& OutLocation) override;
	/*  IHightlightInterface  */
private:

	UPROPERTY(EditAnywhere, Category = "Highlight", meta = (DefautlValue = 0.2f))
	float HightlightDuration = 0.2f;
};
