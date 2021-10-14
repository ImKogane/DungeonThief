// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_SelectSpotCarryFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Food/FoodSpot.h"
#include "DungeonsThief/Managers/FoodManager.h"

EBTNodeResult::Type UBT_SelectSpotCarryFood::CodeToExecute()
{
	AFoodManager* FoodManager = Cast<AFoodManager>(BlackboardComponent->GetValueAsObject("FoodManager"));

	TArray<AFoodSpot*> AllSpotInWorld = FoodManager->GetAllSpotInGame();
	TArray<AFoodSpot*> AlreadyVisitedSpot = AICharacter->GetAlreadyVisitedSpot();
	
	UE_LOG(LogTemp, Warning, TEXT("Already visited spot : %d"), AlreadyVisitedSpot.Num())
	if(AllSpotInWorld.Num() > AlreadyVisitedSpot.Num())
	{
		AFoodSpot* SpotSelected = SelectRandomFoodSpot(AllSpotInWorld);
		while(AlreadyVisitedSpot.Contains(SpotSelected))
		{
			SpotSelected = SelectRandomFoodSpot(AllSpotInWorld);
		}

		BlackboardComponent->SetValueAsObject("SpotLocationToGo", SpotSelected);
		
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
