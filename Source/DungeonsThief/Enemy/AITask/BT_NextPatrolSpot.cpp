// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_NextPatrolSpot.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"

EBTNodeResult::Type UBT_NextPatrolSpot::CodeToExecute()
{

	FVector LocationToRemove = BlackboardComponent->GetValueAsVector("LocationForPatrol");
	
	AICharacter->RemoveLocationForPatrol(LocationToRemove);
	
	return EBTNodeResult::Succeeded;
}
