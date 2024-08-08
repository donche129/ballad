// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BalladCharacterBase.h"

ABalladCharacterBase::ABalladCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ABalladCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABalladCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

