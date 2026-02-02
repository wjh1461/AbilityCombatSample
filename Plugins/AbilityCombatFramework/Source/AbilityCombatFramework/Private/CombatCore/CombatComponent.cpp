// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCore/CombatComponent.h"
#include "AbilitySystemComponent.h"
#include "CombatLog.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCombatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	AbilitySystemComponent = GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogCombat, Warning, TEXT("액터에 AbilitySystemComponent 추가해야함."));
	}
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UAbilitySystemComponent* UCombatComponent::GetAbilitySystemComponent() const
{
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogCombat, Warning, TEXT("AbilitySystemComponent가 존재하지 않음."));
		return nullptr;
	}
	
	return AbilitySystemComponent;
}

void UCombatComponent::RegisterCombatAbilities()
{
	
}

void UCombatComponent::HandleCombatIntent()
{
	//TODO: 전투 입력 해석 후 어빌리티 실행
}

bool UCombatComponent::TryCombatAbility(FGameplayTag CombatGameplayTag)
{
	//TODO: 등록된 태그와 일치하는 어빌리티 실행 시도
	
	
	return true;
}

