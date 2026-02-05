// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "CombatInput/CombatInputConfig.h"
#include "CombatEnhancedInputSubsystem.generated.h"

class UCombatComponent;
struct FGameplayAbilitySpecHandle;
class UAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class ABILITYCOMBATFRAMEWORK_API UCombatEnhancedInputSubsystem : public UEnhancedInputLocalPlayerSubsystem
{
	GENERATED_BODY()
	
protected:
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
public:
	void SetAbilitySystemComponent(UAbilitySystemComponent* NewAbilitySystemComponent) { AbilitySystemComponent = NewAbilitySystemComponent; }
	
	void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	
	void AbilityInputTagPressed(UCombatComponent* CombatComponent, const FGameplayTag CombatInputTag);
	void AbilityInputTagReleased(UCombatComponent* CombatComponent, const FGameplayTag CombatInputTag);
	
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindCombatAbilityActions(UEnhancedInputComponent* InputComponent, UCombatComponent* CombatComponent,
		const UCombatInputConfig* CombatInputConfig, 
	 	UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UCombatEnhancedInputSubsystem::BindCombatAbilityActions(UEnhancedInputComponent* InputComponent, UCombatComponent* CombatComponent,
	const UCombatInputConfig* CombatInputConfig, UserClass* Object, PressedFuncType PressedFunc,
	ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{
	check(CombatInputConfig);
	check(InputComponent);

	for (const FCombatInputAction& Action : CombatInputConfig->CombatAbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				uint32 BindHandle = InputComponent->BindAction(Action.InputAction, ETriggerEvent::Triggered, 
					Object, PressedFunc, CombatComponent, Action.InputTag).GetHandle();
				BindHandles.Add(BindHandle);
			}

			if (ReleasedFunc)
			{
				uint32 BindHandle = InputComponent->BindAction(Action.InputAction, ETriggerEvent::Completed, 
					Object, ReleasedFunc, CombatComponent, Action.InputTag).GetHandle();
				BindHandles.Add(BindHandle);
			}
		}
	}
}
