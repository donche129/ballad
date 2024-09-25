// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BalladAIController.generated.h"
class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class BALLAD_API ABalladAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABalladAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
