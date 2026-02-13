// Fill out your copyright notice in the Description page of Project Settings.


#include "Targeting/TargetingComponent.h"

#include "CombatLog.h"

// Sets default values for this component's properties
UTargetingComponent::UTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

APawn* UTargetingComponent::GetMainTargetPawn() const
{
	return MainTargetPawn;
}

void UTargetingComponent::FocusMainTargetPawn()
{
	//TODO: 메인 타겟이 변경되지 않게 고정
	
	UE_LOG(LogCombat, Log, TEXT("FocusMainTargetPawn"));
}

void UTargetingComponent::FindMainTargetPawn()
{
	//TODO: 특정 범위 내에서 메인 타겟 찾기
	
	// 카메라가 바라보는 방향, 폰이 바라보는 방향
	// 포함 시킬 범위
	// 우선순위 문제
	
	UE_LOG(LogCombat, Log, TEXT("FindMainTargetPawn"));
}

void UTargetingComponent::PerformTargeting()
{
	UE_LOG(LogCombat, Log, TEXT("Combat 타겟 찾기"));
}

