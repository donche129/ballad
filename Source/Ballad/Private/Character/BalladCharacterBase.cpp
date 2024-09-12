// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BalladCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/BalladAbilitySystemComponent.h"
#include "Ballad/Ballad.h"
#include "Components/CapsuleComponent.h"

ABalladCharacterBase::ABalladCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

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

FVector ABalladCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

void ABalladCharacterBase::InitAbilityActorInfo()
{
}

void ABalladCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ABalladCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ABalladCharacterBase::AddCharacterAbilities()
{
	UBalladAbilitySystemComponent* BalladASC = CastChecked<UBalladAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	BalladASC->AddCharacterAbilities(StartupAbilities);
}
