// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

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
	
protected:
	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;
	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;
	
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
	
	// 사용할 어빌리티들을 등록
	void RegisterCombatAbilities();
	
	// 전투 입력 의도 처리
	virtual void HandleCombatIntent();
	
	
	//---------------------- 입력 관련
	//TODO: 이 부분은 서브시스템으로 분리할 수 있다면 분리
	void InitializePlayerInput(UInputComponent* PlayerInputComponent);
	// 입력 처리 관련 메서드. 입력 태그에 매칭되는 어빌리티를 실행
	void AbilityInputTagPressed(const FGameplayTag CombatInputTag);
	void AbilityInputTagReleased(const FGameplayTag CombatInputTag);
	// 입력 타이밍 처리 문제
	void ProcessAbilityInput(const float DeltaTime, const bool bGamePaused);
};
