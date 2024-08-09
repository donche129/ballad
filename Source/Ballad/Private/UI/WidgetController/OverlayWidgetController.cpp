// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/BalladAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UBalladAttributeSet* BalladAttributeSet = CastChecked<UBalladAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(BalladAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BalladAttributeSet->GetMaxHealth());
}
