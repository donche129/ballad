// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/BalladAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "BalladGameplayTags.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{

}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UBalladAttributeSet* AS = CastChecked<UBalladAttributeSet>(AttributeSet);

	check(AttributeInfo);

	FBalladAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FBalladGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}
