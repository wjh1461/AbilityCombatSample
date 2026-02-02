// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "CombatAttributeSet.generated.h"

/**
 *  전투 관련 기본 속성들
 *  공격력, 방어력, 크리티컬 확률, 크리티컬 피해
 *  
 */
UCLASS()
class ABILITYCOMBATFRAMEWORK_API UCombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UCombatAttributeSet();
	
private:
	UPROPERTY()
	FGameplayAttributeData BaseDamage;
	UPROPERTY()
	FGameplayAttributeData BaseDefense;
};
