// Copyright CS_WUXIA 

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Character.h"
#include "CSWuxiaAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

struct FCharacterRow;

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	
	FEffectProperties(){}
	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;
	
	UPROPERTY()
	AActor* TargetAvatarActor= nullptr;
	
	UPROPERTY()
	AController* TargetController= nullptr;
	
	UPROPERTY()
	ACharacter* TargetCharacter= nullptr;
};

// Typedef for attribute getter function pointer but TStaticFuncPtr is generic to any signature chose
// 屬性獲取函數指標的 typedef，但 TStaticFuncPtr 是通用的，可以選擇任何簽名
// typedef TBaseStaticDelegateInstance<FGameplayAttribute(),FDefaultDelegateUserPolicy>::FFuncPtr  FAttributeGetFuncPtr;
template<class T>
using TStaticFuncPtr = TBaseStaticDelegateInstance<T,FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class CS_WUXIA_API UCSWuxiaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UCSWuxiaAttributeSet();

	void InitializeAttributesFromRow(const FCharacterRow& CharacterRow);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	void Debuff(const FEffectProperties& Props);

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributeMap;

	UPROPERTY(ReplicatedUsing = OnRep_Attack, BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UCSWuxiaAttributeSet, Attack)
	
	UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, Category = "Base Attributes") 
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCSWuxiaAttributeSet, Health)

	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCSWuxiaAttributeSet, MaxHealth)

	UPROPERTY(ReplicatedUsing = OnRep_ActionPoint, BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData ActionPoint;
	ATTRIBUTE_ACCESSORS(UCSWuxiaAttributeSet, ActionPoint)

	UPROPERTY(ReplicatedUsing = OnRep_MaxActionPoint, BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData MaxActionPoint;
	ATTRIBUTE_ACCESSORS(UCSWuxiaAttributeSet, MaxActionPoint)

	UPROPERTY(ReplicatedUsing = OnRep_Defense, BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UCSWuxiaAttributeSet, Defense)

	UPROPERTY(ReplicatedUsing = OnRep_DistancePerAP, BlueprintReadOnly, Category = "Base Attributes")
	FGameplayAttributeData DistancePerAP;
	ATTRIBUTE_ACCESSORS(UCSWuxiaAttributeSet, DistancePerAP)
	

	/*Meta  Attributes*/
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UCSWuxiaAttributeSet, IncomingDamage)

	
protected:

	UFUNCTION()
	virtual void OnRep_Attack(const FGameplayAttributeData& OldAttack);
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	UFUNCTION()
	virtual void OnRep_ActionPoint(const FGameplayAttributeData& OldActionPoint);
	UFUNCTION()
	virtual void OnRep_MaxActionPoint(const FGameplayAttributeData& OldMaxActionPoint);
	UFUNCTION()
	virtual void OnRep_Defense(const FGameplayAttributeData& OldDefense);
	UFUNCTION()
	virtual void OnRep_DistancePerAP(const FGameplayAttributeData& OldDistancePerAP);

private:
	void HandleIncomingDamage(const FEffectProperties& Props) ;

	static void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);


	int BaseActionPoint = 10;
	//每一AP走的距離
	float BaseDistancePerAP = 100.f;
	
};

