// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BalladAbilitySystemGlobals.h"

#include "BalladAbilityTypes.h"

FGameplayEffectContext* UBalladAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FBalladGameplayEffectContext();
}
