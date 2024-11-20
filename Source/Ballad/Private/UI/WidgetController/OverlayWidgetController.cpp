// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/BalladAbilitySystemComponent.h"
#include "AbilitySystem/BalladAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UBalladAttributeSet* BalladAttributeSet = CastChecked<UBalladAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(BalladAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BalladAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(BalladAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(BalladAttributeSet->GetMaxMana());

}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UBalladAttributeSet* BalladAttributeSet = CastChecked<UBalladAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BalladAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BalladAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BalladAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BalladAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);

	if (UBalladAbilitySystemComponent* BalladASC = Cast<UBalladAbilitySystemComponent>(AbilitySystemComponent))
	{
		if (BalladASC->bStartupAbilitiesGiven)
		{
			OnInitializeStartupAbilities(BalladASC);
		}
		else
		{
			BalladASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}
		
		BalladASC->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					// For example, say that Tag = Message.HealthPotion
					// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UBalladAbilitySystemComponent* BalladAbilitySystemComponent)
{
	// TODO: Get information about all given abilities, look up their Ability Info, and broadcast it to widgets.
	if (!BalladAbilitySystemComponent->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		// TODO: need a way to figure out the ability tag for a given ability spec.
		FBalladAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(UBalladAbilitySystemComponent::GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = UBalladAbilitySystemComponent::GetInputTagFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	BalladAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}
