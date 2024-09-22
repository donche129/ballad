// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BalladGameplayAbility.h"
#include "BalladDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BALLAD_API UBalladDamageGameplayAbility : public UBalladGameplayAbility
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
