// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CombatGameplayAbilityBase.generated.h"

class UCombatComponent;

UENUM(BlueprintType)
enum class ECombatAbilityActivationPolicy : uint8
{
	OnInputTriggered,
	WhileInputActive,
	
};

/**
 * 
 */
UCLASS(Abstract)
class ABILITYCOMBATFRAMEWORK_API UCombatGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
	UCombatGameplayAbilityBase();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat|Ability Activation")
	ECombatAbilityActivationPolicy ActivationPolicy;
	
public:
	ECombatAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }
	
	UFUNCTION(BlueprintCallable, Category="Combat|CombatAbility")
	UCombatComponent* GetCombatComponent() const;
};
