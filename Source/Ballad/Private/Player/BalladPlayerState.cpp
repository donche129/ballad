// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BalladPlayerState.h"

#include "AbilitySystem/BalladAbilitySystemComponent.h"
#include "AbilitySystem/BalladAttributeSet.h"
#include "Net/UnrealNetwork.h"

ABalladPlayerState::ABalladPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBalladAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UBalladAttributeSet>("AttributeSet");

	NetUpdateFrequency = 100.f;
}

void ABalladPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABalladPlayerState, Level);
}

UAbilitySystemComponent* ABalladPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABalladPlayerState::OnRep_Level(int32 OldLevel)
{

}
