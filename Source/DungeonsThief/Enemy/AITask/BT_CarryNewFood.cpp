// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_CarryNewFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Food/Food.h"
#include "DungeonsThief/Managers/FoodManager.h"

EBTNodeResult::Type UBT_CarryNewFood::CodeToExecute()
{
	//get FoodManager
	AFoodManager* FoodManager = Cast<AFoodManager>(BlackboardComponent->GetValueAsObject("FoodManager"));

	if (FoodManager)
	{
		//spawn food on the AICharacter
		AActor* FoodToCarry = FoodManager->SpawnFood(AICharacter->GetActorLocation());
		if(FoodToCarry)
		{
			//Then let him Carry the food
			AICharacter->SetNearFoodActor(FoodToCarry);
			AICharacter->InteractWithItem();
			FoodManager->GlobalWaitTest = false;
			BlackboardComponent->SetValueAsObject("FoodCarrying", FoodToCarry);
			BlackboardComponent->SetValueAsInt("HasARole", 1);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
