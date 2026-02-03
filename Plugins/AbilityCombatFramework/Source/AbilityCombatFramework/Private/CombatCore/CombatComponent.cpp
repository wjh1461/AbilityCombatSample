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
	//
}

void UCombatComponent::HandleCombatIntent()
{
	//TODO: 전투 입력 해석 후 어빌리티 실행
}

void UCombatComponent::AbilityInputTagPressed(const FGameplayTag CombatInputTag)
{
	if (CombatInputTag.IsValid() && AbilitySystemComponent)
	{
		TArray<FGameplayAbilitySpec>& ActivatableAbilities = AbilitySystemComponent->GetActivatableAbilities();
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities)
		{
			if (AbilitySpec.Ability && AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(CombatInputTag))
			{
				InputPressedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UCombatComponent::AbilityInputTagReleased(const FGameplayTag CombatInputTag)
{
	if (CombatInputTag.IsValid())
	{
		TArray<FGameplayAbilitySpec>& ActivatableAbilities = AbilitySystemComponent->GetActivatableAbilities();
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities)
		{
			if (AbilitySpec.Ability && AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(CombatInputTag))
			{
				InputReleasedSpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.Remove(AbilitySpec.Handle);
			}
		}
	}
}

void UCombatComponent::ProcessAbilityInput(const float DeltaTime, const bool bGamePaused)
{
	//TODO: InputPressedSpecHandles, InputReleasedSpecHandles, InputHeldSpecHandles 처리
	// 기존 플레이어 입력 시스템과 충돌하지 않아야 함.
	
	UE_LOG(LogCombat, Log, TEXT("ProcessAbilityInput Tick 처리"));
	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	// Input Held
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	{
		if (const FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability && !AbilitySpec->IsActive())
			{
				//TODO: 
			}
		}
	}
	
	// Input Pressed
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = true;
				if (AbilitySpec->IsActive())
				{
					//AbilitySpecInputPressed(*AbilitySpec);	
				}
				else
				{
					//TODO: 
				}
			}
		}
	}

	// 어빌리티 실행
	for (const FGameplayAbilitySpecHandle& AbilitySpecHandle : AbilitiesToActivate)
	{
		AbilitySystemComponent->TryActivateAbility(AbilitySpecHandle);
	}
	
	// Input Released
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = false;
				if (AbilitySpec->IsActive())
				{
					//AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}
	
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

