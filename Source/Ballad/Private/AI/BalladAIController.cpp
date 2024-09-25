// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BalladAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ABalladAIController::ABalladAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);
}
