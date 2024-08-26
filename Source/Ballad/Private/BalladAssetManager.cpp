// Fill out your copyright notice in the Description page of Project Settings.


#include "BalladAssetManager.h"
#include "BalladGameplayTags.h"

UBalladAssetManager& UBalladAssetManager::Get()
{
	check(GEngine);

	UBalladAssetManager* BalladAssetManager = Cast<UBalladAssetManager>(GEngine->AssetManager);
	return *BalladAssetManager;
}

void UBalladAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FBalladGameplayTags::InitializeNativeGameplayTags();
}
