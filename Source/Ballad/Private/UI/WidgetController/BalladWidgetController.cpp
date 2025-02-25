// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/BalladWidgetController.h"

void UBalladWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UBalladWidgetController::BroadcastInitialValues()
{

}

void UBalladWidgetController::BindCallbacksToDependencies()
{

}
