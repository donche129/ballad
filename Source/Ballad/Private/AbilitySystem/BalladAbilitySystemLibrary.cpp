// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BalladAbilitySystemLibrary.h"
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
