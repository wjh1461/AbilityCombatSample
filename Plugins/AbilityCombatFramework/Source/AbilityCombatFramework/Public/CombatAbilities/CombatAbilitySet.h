// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CombatAbilitySet.generated.h"

class UCombatGameplayAbilityBase;

USTRUCT(BlueprintType)
struct FCombatAbilitySet_GameplayAbility
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCombatGameplayAbilityBase> Ability;
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;
};

/**
 * 
 */
UCLASS()
class ABILITYCOMBATFRAMEWORK_API UCombatAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Combat Ability")
	TArray<FCombatAbilitySet_GameplayAbility> GrantedCombatAbilities;
};
