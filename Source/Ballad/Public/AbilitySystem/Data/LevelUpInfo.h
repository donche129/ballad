// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FBalladLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointReward = 1;

	UPROPERTY(EditDefaultsOnly)
	int32 SpellPointReward = 1;
};

/**
 * 
 */
UCLASS()
class BALLAD_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	TArray<FBalladLevelUpInfo> LevelUpInformation;

	int32 FindLevelForXP(int32 XP) const;
};
