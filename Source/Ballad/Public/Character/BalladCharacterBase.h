// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BalladCharacterBase.generated.h"

UCLASS(Abstract)
class BALLAD_API ABalladCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABalladCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
