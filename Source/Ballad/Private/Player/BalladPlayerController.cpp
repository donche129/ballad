// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BalladPlayerController.h"

#include "EnhancedInputSubsystems.h"

ABalladPlayerController::ABalladPlayerController()
{
	bReplicates = true;
}

void ABalladPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(BalladContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(BalladContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
