// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatAbilities/CombatAbilitySet.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "CombatAbilities/CombatGameplayAbilityBase.h"

void UCombatAbilitySet::GiveCombatAbilitySystem(UAbilitySystemComponent* ASC, UObject* SourceObject) const
{
	check(ASC);
	
	// 어빌리티 부여
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedCombatAbilities.Num(); AbilityIndex++)
	{
		const FCombatAbilitySet_GameplayAbility& AbilityToGrant = GrantedCombatAbilities[AbilityIndex];
		if (!IsValid(AbilityToGrant.Ability))
		{
			continue;
		}

		UCombatGameplayAbilityBase* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UCombatGameplayAbilityBase>();
		FGameplayAbilitySpec AbilitySpec{ AbilityCDO, AbilityToGrant.AbilityLevel };
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityToGrant.InputTag);

		const FGameplayAbilitySpecHandle AbilitySpecHandle = ASC->GiveAbility(AbilitySpec);

		// if (OutGrantedHandles)
		// {
		// 	OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		// }
	}
}
