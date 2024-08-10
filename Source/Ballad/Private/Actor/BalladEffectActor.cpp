// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BalladEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/BalladAttributeSet.h"
#include "Components/SphereComponent.h"

ABalladEffectActor::ABalladEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void ABalladEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a Gameplay Effect. For now, using const_cast as a hack!
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UBalladAttributeSet* BalladAttributeSet = Cast<UBalladAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UBalladAttributeSet::StaticClass()));

		UBalladAttributeSet* MutableBalladAttributeSet = const_cast<UBalladAttributeSet*>(BalladAttributeSet);
		MutableBalladAttributeSet->SetHealth(BalladAttributeSet->GetHealth() + 25.f);
		MutableBalladAttributeSet->SetMana(BalladAttributeSet->GetMana() - 25.f);
		Destroy();
	}
}

void ABalladEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void ABalladEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABalladEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ABalladEffectActor::EndOverlap);
}
