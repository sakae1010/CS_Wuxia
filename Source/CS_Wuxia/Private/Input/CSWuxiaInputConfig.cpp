// Copyright CS_WUXIA 


#include "Input/CSWuxiaInputConfig.h"

const UInputAction* UCSWuxiaInputConfig::GetAbilityInputActionForTag(const FGameplayTag& InputTag,bool bLogNotFound) const
{
	for (const auto& [InputAction, GameplayTag] : InputActions)
	{
		if (InputAction && GameplayTag.MatchesTag(InputTag))
		{
			return InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("No InputAction found for tag %s , on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
