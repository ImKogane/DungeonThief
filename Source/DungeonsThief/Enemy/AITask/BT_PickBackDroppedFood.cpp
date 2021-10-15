// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_PickBackDroppedFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Food/Food.h"
#include "DungeonsThief/Managers/FoodManager.h"

EBTNodeResult::Type UBT_PickBackDroppedFood::CodeToExecute()
{	
	AFood* FoodDroped = Cast<AFood>(BlackboardComponent->GetValueAsObject("FoodDropped"));
	
	//TODO Peut être améliorer je pense
	if(FoodDroped == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoodDroped not found"))
		return EBTNodeResult::Failed;
	}
	
	float DistanceFromFoodDropped = FVector::Dist(FoodDroped->GetActorLocation(), AICharacter->GetActorLocation());

	if(DistanceFromFoodDropped <= 150)
	{	
		AICharacter->SetNearFoodActor(FoodDroped);
		AICharacter->InteractWithItem();
		BlackboardComponent->SetValueAsObject("FoodCarrying", FoodDroped);
		BlackboardComponent->ClearValue("FoodDropped");
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
