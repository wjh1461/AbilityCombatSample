// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "EnhancedInputComponent.h"
#include "GameplayAbilitySpec.h"
#include "Components/ActorComponent.h"
#include "CombatInput/CombatInputConfig.h"
#include "CombatComponent.generated.h"

class UCombatAbilityProfile;
class UInputMappingContext;
class UCombatAbilitySet;
struct FGameplayTag;

/**
 * 전투 시스템을 담당하는 핵심 컴포넌트
 * 기존 AbilitySystemComponent를 사용 중이면 호환 가능하게끔 구성.
 * 허브 역할
 * 
 * 
 * 어빌리티 태그 사용
 * (입력 - 태그) -> (태그 -> GA 실행)
 * Combat.Ability.PrimaryAction
 * Combat.Attribute.Attack
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABILITYCOMBATFRAMEWORK_API UCombatComponent : public UActorComponent, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();
	
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCombatAbilityProfile> CombatAbilityProfile;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UInputMappingContext>> DefaultInputMappings;
	
private:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//~Begin IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End
	
	UInputComponent* GetInputComponent() const;
	UCombatInputConfig* GetCombatInputConfig() const;
	
	// 사용할 어빌리티들을 등록
	void RegisterCombatAbilities();
	
	// 전투 입력 의도 처리
	virtual void HandleCombatIntent();
	
	//---------------------- 입력 관련
	//TODO: 입력 타이밍 처리 문제가 발생할 수 있음
	void ProcessAbilityInput(const float DeltaTime, const bool bGamePaused);
};
