// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCore/CombatComponent.h"
#include "AbilitySystemComponent.h"
#include "CombatLog.h"
#include "CombatAbilities/CombatAbilitySet.h"
#include "CombatAbilities/CombatGameplayAbilityBase.h"
#include "Subsystems/CombatEnhancedInputSubsystem.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	APawn* Pawn = Cast<APawn>(GetOwner());
	const APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());
	const ULocalPlayer* LP = PlayerController->GetLocalPlayer();
	UCombatEnhancedInputSubsystem* Subsystem = LP->GetSubsystem<UCombatEnhancedInputSubsystem>();
	
	Subsystem->InitializePlayerInput(this);
	RegisterCombatAbilities();
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

	//TODO: 입력 처리는 일단 틱에서 관리 
	// 틱 관련 문제가 생길 경우 FTickFunction을 상속받아 해결
	bool bGamePaused = false; 
	ProcessAbilityInput(DeltaTime, bGamePaused);
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

UInputComponent* UCombatComponent::GetInputComponent() const
{
	return GetOwner()->InputComponent;
}

UCombatInputConfig* UCombatComponent::GetCombatInputConfig() const
{
	return CombatInputConfig;
}

void UCombatComponent::RegisterCombatAbilities()
{
	CombatAbilitySet->GiveCombatAbilitySystem(AbilitySystemComponent);
}

void UCombatComponent::HandleCombatIntent()
{
	//TODO: 전투 입력 해석 후 어빌리티 실행 
}

void UCombatComponent::ProcessAbilityInput(const float DeltaTime, const bool bGamePaused)
{
	//TODO: InputPressedSpecHandles, InputReleasedSpecHandles, InputHeldSpecHandles 처리
	// 기존 플레이어 입력 시스템과 충돌하지 않아야 함.
	// 입력이 Blocked 되었을 경우 처리
	
	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	// Input Held
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	{
		if (const FGameplayAbilitySpec* AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability && !AbilitySpec->IsActive())
			{
				const UCombatGameplayAbilityBase* CombatAbilityCDO = Cast<UCombatGameplayAbilityBase>(AbilitySpec->Ability);
				if (CombatAbilityCDO && 
					CombatAbilityCDO->GetActivationPolicy() == ECombatAbilityActivationPolicy::WhileInputActive)
				{
					AbilitiesToActivate.AddUnique(SpecHandle);
				}
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
					AbilitySystemComponent->AbilitySpecInputPressed(*AbilitySpec);	
				}
				else
				{
					const UCombatGameplayAbilityBase* CombatAbilityCDO = Cast<UCombatGameplayAbilityBase>(AbilitySpec->Ability);
					if (CombatAbilityCDO && 
						CombatAbilityCDO->GetActivationPolicy() == ECombatAbilityActivationPolicy::OnInputTriggered)
					{
						AbilitiesToActivate.AddUnique(SpecHandle);
					}
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
					AbilitySystemComponent->AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}
	
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

