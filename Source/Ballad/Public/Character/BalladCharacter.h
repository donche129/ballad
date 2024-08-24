// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BalladCharacterBase.h"
#include "BalladCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BALLAD_API ABalladCharacter : public ABalladCharacterBase
{
	GENERATED_BODY()
public:
	ABalladCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface */
	virtual int32 GetPlayerLevel() override;
	/** end Combat Interface */

private:
	virtual void InitAbilityActorInfo() override;
};
