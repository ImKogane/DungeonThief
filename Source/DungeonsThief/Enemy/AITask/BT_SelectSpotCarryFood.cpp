// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_SelectSpotCarryFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Food/FoodSpot.h"
#include "DungeonsThief/Managers/FoodManager.h"

EBTNodeResult::Type UBT_SelectSpotCarryFood::CodeToExecute()
{
	AFoodManager* FoodManager = Cast<AFoodManager>(BlackboardComponent->GetValueAsObject("FoodManager"));

	TArray<AFoodSpot*> AllSpotInWorld = FoodManager->GetAllSpotInGame();
	if(AllSpotInWorld.Num() > AlreadyVisitedSpot.Num())
	{
		AFoodSpot* SpotSelected = SelectRandomFoodSpot(AllSpotInWorld);
		while(AlreadyVisitedSpot.Contains(SpotSelected))
		{
			SpotSelected = SelectRandomFoodSpot(AllSpotInWorld);
		}

		BlackboardComponent->SetValueAsObject("SpotLocationToGo", SpotSelected);
		AlreadyVisitedSpot.Add(SpotSelected);
			
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
