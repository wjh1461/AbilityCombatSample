// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CombatAbilityProfile.generated.h"

class UCombatAbilitySet;
class UCombatInputConfig;

/**
 * 
 */
UCLASS()
class ABILITYCOMBATFRAMEWORK_API UCombatAbilityProfile : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCombatAbilitySet> CombatAbilitySet;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCombatInputConfig> CombatInputConfig;
};
