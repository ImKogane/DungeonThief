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
	if(FoodDroped)
	{
		float DistBetweenBoth = FVector::Dist(FoodDroped->GetActorLocation(), AICharacter->GetActorLocation());

		if(DistBetweenBoth <= 150)
		{
			UE_LOG(LogTemp, Warning, TEXT("FOUND IT OMG"))
			AICharacter->SetNearFoodActor(FoodDroped);
			AICharacter->InteractWithItem();
			BlackboardComponent->SetValueAsObject("FoodCarrying", FoodDroped);
			BlackboardComponent->ClearValue("FoodDropped");
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}
