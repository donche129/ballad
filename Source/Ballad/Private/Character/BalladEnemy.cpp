// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BalladEnemy.h"

#include "AbilitySystem/BalladAbilitySystemComponent.h"
#include "AbilitySystem/BalladAbilitySystemLibrary.h"
#include "AbilitySystem/BalladAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Ballad/Ballad.h"
#include "UI/Widget/BalladUserWidget.h"
#include "BalladGameplayTags.h"
#include "AI/BalladAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ABalladEnemy::ABalladEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UBalladAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<UBalladAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
}

void ABalladEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	BalladAIController = Cast<ABalladAIController>(NewController);

	BalladAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	BalladAIController->RunBehaviorTree(BehaviorTree);
	BalladAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	BalladAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);
}

void ABalladEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ABalladEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 ABalladEnemy::GetPlayerLevel()
{
	return Level;
}

void ABalladEnemy::Die()
{
	SetLifeSpan(LifeSpan	);
	Super::Die();
}

void ABalladEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ABalladEnemy::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void ABalladEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UBalladAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	}

	if (UBalladUserWidget* BalladUserWidget = Cast<UBalladUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		BalladUserWidget->SetWidgetController(this);
	}
	
	if (const UBalladAttributeSet* BalladAS = CastChecked<UBalladAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BalladAS->GetHealthAttribute()).AddLambda(
			[this, BalladAS](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
				/**
				 * Below is a potential fix for a bug where the enemy health bar widget remains at a value of zero
				 * and is therefore not visible on the client side.
				 * Somehow the value is not replicating to clients when using Data.NewValue.
				 */
				// OnHealthChanged.Broadcast(Data.Attribute.GetNumericValue(BalladAS));
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BalladAS->GetMaxHealthAttribute()).AddLambda(
			[this, BalladAS](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
				/**
				 * Below is a potential fix for a bug where the enemy health bar widget remains at a value of zero
				 * and is therefore not visible on the client side.
				 * Somehow the value is not replicating to clients when using Data.NewValue.
				 */
				// OnMaxHealthChanged.Broadcast(Data.Attribute.GetNumericValue(BalladAS));
			}
		);
		
		AbilitySystemComponent->RegisterGameplayTagEvent(FBalladGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&ABalladEnemy::HitReactTagChanged
		);

		OnHealthChanged.Broadcast(BalladAS->GetHealth());
		OnMaxHealthChanged.Broadcast(BalladAS->GetMaxHealth());
	}
}

void ABalladEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	BalladAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
}

void ABalladEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UBalladAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}

void ABalladEnemy::InitializeDefaultAttributes() const
{
	UBalladAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
