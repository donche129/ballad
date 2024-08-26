// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BalladAbilitySystemComponent.h"

#include "BalladGameplayTags.h"

void UBalladAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UBalladAbilitySystemComponent::EffectApplied);

	const FBalladGameplayTags& GameplayTags = FBalladGameplayTags::Get();

	GEngine->AddOnScreenDebugMessage(
		-1,
		10.f,
		FColor::Orange,
		FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armor.ToString())
	);
}

void UBalladAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	
	EffectAssetTags.Broadcast(TagContainer);
}
