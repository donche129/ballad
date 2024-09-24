// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BalladAbilitySystemLibrary.h"

#include "BalladAbilityTypes.h"
#include "Game/BalladGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/BalladPlayerState.h"
#include "UI/HUD/BalladHUD.h"
#include "UI/WidgetController/BalladWidgetController.h"

UOverlayWidgetController* UBalladAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ABalladHUD* BalladHUD = Cast<ABalladHUD>(PC->GetHUD()))
		{
			ABalladPlayerState* PS = PC->GetPlayerState<ABalladPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return BalladHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UBalladAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ABalladHUD* BalladHUD = Cast<ABalladHUD>(PC->GetHUD()))
		{
			ABalladPlayerState* PS = PC->GetPlayerState<ABalladPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return BalladHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void UBalladAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle TertiaryAttributesContextHandle = ASC->MakeEffectContext();
	TertiaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle TertiaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->TertiaryAttributes, Level, TertiaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*TertiaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UBalladAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UBalladAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	ABalladGameModeBase* BalladGameMode = Cast<ABalladGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (BalladGameMode == nullptr) return nullptr;
	return BalladGameMode->CharacterClassInfo;
}

bool UBalladAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBalladGameplayEffectContext* BalladEffectContext = static_cast<const FBalladGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return BalladEffectContext->IsBlockedHit();
	}
	return false;
}

bool UBalladAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBalladGameplayEffectContext* BalladEffectContext = static_cast<const FBalladGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return BalladEffectContext->IsCriticalHit();
	}
	return false;
}

void UBalladAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsBlockedHit)
{
	if (FBalladGameplayEffectContext* BalladEffectContext = static_cast<FBalladGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		BalladEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UBalladAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle,
	bool bInIsCriticalHit)
{
	if (FBalladGameplayEffectContext* BalladEffectContext = static_cast<FBalladGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		BalladEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}
