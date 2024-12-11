// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/BalladAbilitySystemComponent.h"
#include "AbilitySystem/BalladAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Player/BalladPlayerState.h"

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
	ABalladPlayerState* BalladPlayerState = CastChecked<ABalladPlayerState>(PlayerState);
	BalladPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	
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

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	const ABalladPlayerState* BalladPlayerState = CastChecked<ABalladPlayerState>(PlayerState);
	const ULevelUpInfo* LevelUpInfo = BalladPlayerState->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unable to find LevelUpInfo. Please fill out BalladPlayerState Blueprint with a valid LevelUpInfo."));

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num() - 1;

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;

		const int32 DeltaLevelUpRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelUpRequirement);

		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}
