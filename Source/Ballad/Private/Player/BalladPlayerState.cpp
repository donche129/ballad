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
	DOREPLIFETIME(ABalladPlayerState, XP);
}

UAbilitySystemComponent* ABalladPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABalladPlayerState::AddToXP(int32 InXP)
{
	XP += InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void ABalladPlayerState::AddToLevel(int32 InLevel)
{
	Level += InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void ABalladPlayerState::SetXP(int32 InXP)
{
	XP = InXP;
	OnXPChangedDelegate.Broadcast(XP);
}

void ABalladPlayerState::SetLevel(int32 InLevel)
{
	Level = InLevel;
	OnLevelChangedDelegate.Broadcast(Level);
}

void ABalladPlayerState::OnRep_Level(int32 OldLevel)
{
	OnLevelChangedDelegate.Broadcast(Level);
}

void ABalladPlayerState::OnRep_XP(int32 OldXP)
{
	OnXPChangedDelegate.Broadcast(XP);
}
