// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BalladCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/BalladPlayerController.h"
#include "Player/BalladPlayerState.h"
#include "UI/HUD/BalladHUD.h"

ABalladCharacter::ABalladCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ABalladCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the server
	InitAbilityActorInfo();
}

void ABalladCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the client
	InitAbilityActorInfo();
}

void ABalladCharacter::InitAbilityActorInfo()
{
	ABalladPlayerState* BalladPlayerState = GetPlayerState<ABalladPlayerState>();
	check(BalladPlayerState);
	BalladPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BalladPlayerState, this);
	AbilitySystemComponent = BalladPlayerState->GetAbilitySystemComponent();
	AttributeSet = BalladPlayerState->GetAttributeSet();

	if (ABalladPlayerController* BalladPlayerController = Cast<ABalladPlayerController>(GetController()))
	{
		if (ABalladHUD* BalladHUD = Cast<ABalladHUD>(BalladPlayerController->GetHUD()))
		{
			BalladHUD->InitOverlay(BalladPlayerController, BalladPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
