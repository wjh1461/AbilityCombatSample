// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CombatEnhancedInputSubsystem.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "CombatCore/CombatComponent.h"

void UCombatEnhancedInputSubsystem::InitializePlayerInput(UCombatComponent* CombatComponent)
{
	check(CombatComponent);
	
	const APawn* Pawn = Cast<APawn>(CombatComponent->GetOwner());
	if (!Pawn)
	{
		return;
	}
	
	const APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
	check(PC);
	
	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PC->GetLocalPlayer());
	check(LocalPlayer);
	
	UCombatEnhancedInputSubsystem* Subsystem = LocalPlayer->GetSubsystem<UCombatEnhancedInputSubsystem>();
	check(Subsystem);

	UCombatInputConfig* CombatInputConfig = CombatComponent->GetCombatInputConfig();
	if (CombatInputConfig)
	{
		if (UEnhancedInputComponent* InputComponent = Cast<UEnhancedInputComponent>(CombatComponent->GetInputComponent()))
		{
			TArray<uint32> BindHandles;
			BindCombatAbilityActions(InputComponent, CombatComponent, CombatInputConfig, 
				this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased,
				BindHandles);
			BindCombatAbilityActions(InputComponent, CombatComponent, CombatInputConfig, 
				this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, 
				BindHandles);
		}
	}
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
