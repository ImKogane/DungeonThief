// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_SelectSpotCarryFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Food/FoodSpot.h"
#include "DungeonsThief/Managers/FoodManager.h"

EBTNodeResult::Type UBT_SelectSpotCarryFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
	
	if(AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();
			AFoodManager* FoodManager = Cast<AFoodManager>(BlackboardComponent->GetValueAsObject("FoodManager"));

			TArray<AFoodSpot*> AllSpotInWorld = FoodManager->getAllSpotInGame();
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
		}
	}

	return EBTNodeResult::Failed;
}

AFoodSpot* UBT_SelectSpotCarryFood::SelectRandomFoodSpot(TArray<AFoodSpot*> ActorList)
{
	const int RandomIndex = FMath::FRandRange(0, ActorList.Num());
	return ActorList[RandomIndex];
}
