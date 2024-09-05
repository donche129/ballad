// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BalladGameplayAbility.h"
#include "BalladProjectileSpell.generated.h"

class ABalladProjectile;
/**
 * 
 */
UCLASS()
class BALLAD_API UBalladProjectileSpell : public UBalladGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABalladProjectile> ProjectileClass;
};
