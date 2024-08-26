// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "BalladAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class BALLAD_API UBalladAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UBalladAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
