// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_NextPatrolSpot.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Food/FoodSpot.h"

EBTNodeResult::Type UBT_NextPatrolSpot::CodeToExecute()
{

	AFoodSpot* SpotToRemove = Cast<AFoodSpot>(BlackboardComponent->GetValueAsObject("SpotLocationToGo"));

	if(SpotToRemove == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpotToRemove not found"))
		return EBTNodeResult::Failed;
	}
	AICharacter->RemoveASpotForPatrol(SpotToRemove);
	
	return EBTNodeResult::Succeeded;
}
