// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_TryPuttingFoodOnSpot.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Food/Food.h"
#include "DungeonsThief/Managers/FoodManager.h"

EBTNodeResult::Type UBT_TryPuttingFoodOnSpot::CodeToExecute()
{
	//get all spots from food manager
	AFoodManager* FoodManager = Cast<AFoodManager>(BlackboardComponent->GetValueAsObject("FoodManager"));

	AICharacter->InteractWithItem();
			
	if(!AICharacter->GetFoodCarried())
	{
		AFood* FoodDroped = Cast<AFood>(AICharacter->GetPlayerNearFoodActor());
		if(FoodDroped->GetIsOnSpot())
		{
			BlackboardComponent->ClearValue("FoodCarrying");
			BlackboardComponent->ClearValue("SpotLocationToGo");
			return EBTNodeResult::Succeeded;
		}
		AICharacter->InteractWithItem();
	}
	return EBTNodeResult::Failed;
}
