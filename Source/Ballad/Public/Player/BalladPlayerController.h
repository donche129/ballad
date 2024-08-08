// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BalladPlayerController.generated.h"


class UInputMappingContext;

/**
 * 
 */
UCLASS()
class BALLAD_API ABalladPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABalladPlayerController();
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input Mapping")
	TObjectPtr<UInputMappingContext> BalladContext;
};
