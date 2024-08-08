// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BalladCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "BalladEnemy.generated.h"

/**
 * 
 */
UCLASS()
class BALLAD_API ABalladEnemy : public ABalladCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	ABalladEnemy();

	/** Enemy Interface */
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** end Enemy Interface */

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
};
