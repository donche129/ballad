// Fill out your copyright notice in the Description page of Project Settings.


#include "BalladGameplayTags.h"
#include "GameplayTagsManager.h"

FBalladGameplayTags FBalladGameplayTags::GameplayTags;

void FBalladGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance"));
}
