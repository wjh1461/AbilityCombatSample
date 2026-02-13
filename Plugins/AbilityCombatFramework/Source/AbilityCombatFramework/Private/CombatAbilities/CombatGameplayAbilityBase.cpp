// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatAbilities/CombatGameplayAbilityBase.h"

#include "CombatLog.h"
#include "CombatCore/CombatComponent.h"

UCombatGameplayAbilityBase::UCombatGameplayAbilityBase()
{
}

UCombatComponent* UCombatGameplayAbilityBase::GetCombatComponent() const
{
	if (const APawn* Pawn = Cast<APawn>(CurrentActorInfo->OwnerActor))
	{
		UCombatComponent* CombatComponent = Pawn->FindComponentByClass<UCombatComponent>();
		return CombatComponent;
	}
	
	UE_LOG(LogCombat, Warning, TEXT("아바타 액터에서 CombatComponent를 찾을 수 없음."));
	
	return nullptr;
}
