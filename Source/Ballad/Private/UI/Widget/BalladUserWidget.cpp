// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/BalladUserWidget.h"

void UBalladUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
