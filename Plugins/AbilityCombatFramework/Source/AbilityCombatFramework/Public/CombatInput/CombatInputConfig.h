// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CombatInputConfig.generated.h"

class UInputAction;

/**
 * InputAction을 통해 InputTag를 전달하는 구조
 */
USTRUCT(BlueprintType)
struct FCombatInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;
};

/**
 * InputAction과 InputTag 바인딩을 위한 기본 설정 
 */
UCLASS(BlueprintType)
class ABILITYCOMBATFRAMEWORK_API UCombatInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FCombatInputAction> CombatAbilityInputActions;
};
