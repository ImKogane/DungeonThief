// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_DropFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"

EBTNodeResult::Type UBT_DropFood::CodeToExecute()
{
	AICharacter->InteractWithItem();

	
	UObject* StoreFood = BlackboardComponent->GetValueAsObject("FoodCarrying");
	BlackboardComponent->SetValueAsObject("HadFood", StoreFood);
	BlackboardComponent->ClearValue("FoodCarrying");
	return EBTNodeResult::Succeeded;
	
}
