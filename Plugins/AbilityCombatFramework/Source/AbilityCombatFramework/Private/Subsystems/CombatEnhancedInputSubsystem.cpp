// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CombatEnhancedInputSubsystem.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "CombatCore/CombatComponent.h"

void UCombatEnhancedInputSubsystem::InitializePlayerInput(UInputComponent* PlayerInputComponent)
{
}

void UCombatEnhancedInputSubsystem::AbilityInputTagPressed(UCombatComponent* CombatComponent, const FGameplayTag CombatInputTag)
{
	check(CombatComponent);
	
	UAbilitySystemComponent* ASC = CombatComponent->GetAbilitySystemComponent();
	if (CombatInputTag.IsValid() && ASC)
	{
		TArray<FGameplayAbilitySpec>& ActivatableAbilities = ASC->GetActivatableAbilities();
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities)
		{
			if (AbilitySpec.Ability && AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(CombatInputTag))
			{
				CombatComponent->InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				CombatComponent->InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UCombatEnhancedInputSubsystem::AbilityInputTagReleased(UCombatComponent* CombatComponent, const FGameplayTag CombatInputTag)
{
	check(CombatComponent);
	
	UAbilitySystemComponent* ASC = CombatComponent->GetAbilitySystemComponent();
	
	if (CombatInputTag.IsValid() && ASC)
	{
		TArray<FGameplayAbilitySpec>& ActivatableAbilities = ASC->GetActivatableAbilities();
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities)
		{
			if (AbilitySpec.Ability && AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(CombatInputTag))
			{
				CombatComponent->InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				CombatComponent->InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}
