// Copyright CS_WUXIA 


#include "AbilitySystem/CSWuxiaAttributeSet.h"

#include "CSWuxiaGameplayTags.h"

UCSWuxiaAttributeSet::UCSWuxiaAttributeSet()
{
	const FCSWuxiaGameplayTags& Tags = FCSWuxiaGameplayTags::Get();
	TagsToAttributeMap.Add(Tags.Attribute_Base_Attack, GetAttackAttribute);
	TagsToAttributeMap.Add(Tags.Attribute_Base_Defense, GetDefenseAttribute);
	TagsToAttributeMap.Add(Tags.Attribute_Base_Health, GetHealthAttribute);
	TagsToAttributeMap.Add(Tags.Attribute_Base_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributeMap.Add(Tags.Attribute_Base_ActionPoint, GetActionPointAttribute);
	TagsToAttributeMap.Add(Tags.Attribute_Base_MaxActionPoint, GetMaxActionPointAttribute);
	TagsToAttributeMap.Add(Tags.Attribute_Base_DistancePerAP, GetDistancePerAPAttribute);
}

void UCSWuxiaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );
}

void UCSWuxiaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange( Attribute , NewValue );
}

void UCSWuxiaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute( Data );

	Super::PostGameplayEffectExecute(Data);
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
    /*
     //取得戰鬥介面 並且尚未死亡
	* 	if (Props.TargetCharacter->Implements<UCombatInterface>() && ICombatInterface::Execute_IsDead( Props.TargetCharacter))
	{
		return;
	}
     */
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	
	if(Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		HandleIncomingDamage( Props );
	}
	
}

void UCSWuxiaAttributeSet::Debuff(const FEffectProperties& Props)
{
}

void UCSWuxiaAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange( Attribute , OldValue , NewValue );
}

void UCSWuxiaAttributeSet::OnRep_Attack(const FGameplayAttributeData& OldAttack)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCSWuxiaAttributeSet, Attack, OldAttack);
}

void UCSWuxiaAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCSWuxiaAttributeSet, Health, OldHealth);
}

void UCSWuxiaAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCSWuxiaAttributeSet, MaxHealth, OldMaxHealth);
}

void UCSWuxiaAttributeSet::OnRep_ActionPoint(const FGameplayAttributeData& OldActionPoint)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCSWuxiaAttributeSet, ActionPoint, OldActionPoint);
}

void UCSWuxiaAttributeSet::OnRep_MaxActionPoint(const FGameplayAttributeData& OldMaxActionPoint)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCSWuxiaAttributeSet, MaxActionPoint, OldMaxActionPoint);
}

void UCSWuxiaAttributeSet::OnRep_Defense(const FGameplayAttributeData& OldDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCSWuxiaAttributeSet, Defense, OldDefense);
}

void UCSWuxiaAttributeSet::OnRep_DistancePerAP(const FGameplayAttributeData& OldDistancePerAP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCSWuxiaAttributeSet, DistancePerAP, OldDistancePerAP);
}
void UCSWuxiaAttributeSet::HandleIncomingDamage(const FEffectProperties& Props)
{
	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);
	if(LocalIncomingDamage <= 0.f)return;
	const float NewHealth = GetHealth() - LocalIncomingDamage;
	SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

	/*
	const float bFatal = NewHealth <= 0.f;
	if (bFatal)
	{
		if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor))
		{
			FVector DeadthImpuse = UAuraAbilitySystemLibrary::GetDeathImpulse( Props.EffectContextHandle );
			CombatInterface->Die(DeadthImpuse);
		}
		SendXPEvent(Props);
	}
	else
	{
		if (Props.TargetCharacter->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsBeingShocked(Props.TargetCharacter))
		{
			FGameplayTagContainer HitReactTagContainer;
			HitReactTagContainer.AddTag(FAuraGameplayTags::Get().Effects_HitReact);
			Props.TargetAbilitySystemComponent->TryActivateAbilitiesByTag(HitReactTagContainer);
		}

		const FVector& KnokbackForce = UAuraAbilitySystemLibrary::GetKnokbackForce( Props.EffectContextHandle );
		if(!KnokbackForce.IsNearlyZero(1.f))
		{
			Props.TargetCharacter->LaunchCharacter( KnokbackForce , true , true );
		}
	}

	const bool bIsBlockHit = UAuraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
	const bool bIsCriticalHit = UAuraAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
	ShowFloatingText(Props, LocalIncomingDamage , bIsBlockHit , bIsCriticalHit);

	if (UAuraAbilitySystemLibrary::IsSuccessfulDebuff(Props.EffectContextHandle ))
	{
		Debuff( Props );
	}
	*/
}


void UCSWuxiaAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,FEffectProperties& Props)
{
	// Source = causer of the effect , Target = the target of the effect(owner of the attribute set)
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceAbilitySystemComponent = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if(IsValid(Props.SourceAbilitySystemComponent) && Props.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() && Props.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceAbilitySystemComponent->GetAvatarActor();
		Props.SourceController = Props.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		if(Props.SourceController==nullptr && Props.SourceAvatarActor!=nullptr)
		{
			if(const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Cast<APlayerController>(Pawn->GetController());
			}	
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}
	if( Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.GetAvatarActor();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
