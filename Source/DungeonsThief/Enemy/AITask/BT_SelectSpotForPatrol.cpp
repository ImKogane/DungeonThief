// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_SelectSpotForPatrol.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBT_SelectSpotForPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
	
	if(AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();
			
			//get all spots from food manager
			AFoodManager* FoodManager = Cast<AFoodManager>(BlackboardComponent->GetValueAsObject("FoodManager"));
			
			TArray<AFoodSpot*> AllFoodSpot = FoodManager->getAllSpotInGame();

			//temporary array for selecting spot for the AI
			TArray<AFoodSpot*> SpotsForPatrol;
			if(AllFoodSpot.Num() >= 2)
			{
				for (int i = 0; i < 2; i++)
				{
					AFoodSpot* SelectedFoodSpot = Cast<AFoodSpot>(SelectRandomFoodSpot(AllFoodSpot));
					
					while(SpotsForPatrol.Contains(SelectedFoodSpot))
					{
						SelectedFoodSpot = Cast<AFoodSpot>(SelectRandomFoodSpot(AllFoodSpot));
					}
					SpotsForPatrol.Add(SelectedFoodSpot);
				}

				if(SpotsForPatrol.Num() == 2)
				{
					AICharacter->SetSpotsForPatrol(SpotsForPatrol);
					BlackboardComponent->SetValueAsInt("HasARole", 1);
					FoodManager->GlobalWaitTest = false;
					return EBTNodeResult::Succeeded;
				}
			}
			return EBTNodeResult::Succeeded;
		}
	}

	
	return EBTNodeResult::Failed;
}

AActor* UBT_SelectSpotForPatrol::SelectRandomFoodSpot(TArray<AFoodSpot*> ActorList)
{
	const int RandomIndex = FMath::FRandRange(0, ActorList.Num());
	return ActorList[RandomIndex];
}
