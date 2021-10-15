// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_DropFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Food/Food.h"

EBTNodeResult::Type UBT_DropFood::CodeToExecute()
{
	AICharacter->InteractWithItem();

	
	AFood* StoreFood = Cast<AFood>(BlackboardComponent->GetValueAsObject("FoodCarrying"));

	if(StoreFood == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoodCarrying not found"))
		return EBTNodeResult::Failed;
	}
	
	BlackboardComponent->SetValueAsObject("FoodDropped", StoreFood);
	BlackboardComponent->SetValueAsVector("FoodDropedLocation", StoreFood->GetActorLocation());
	BlackboardComponent->ClearValue("FoodCarrying");
	return EBTNodeResult::Succeeded;
}
