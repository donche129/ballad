// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * BalladGameplayTags
 * 
 * Singleton containing native Gameplay Tags.
 */

struct FBalladGameplayTags
{
public:
	static const FBalladGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();
protected:

private:
	static FBalladGameplayTags GameplayTags;
};
