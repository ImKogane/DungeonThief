// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_SelectSpotFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBT_SelectSpotFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if(AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();

			//TODO avoir une référence pour le foodmanager dans le blackboard
			/*//get all spots from food manager
			TArray<AFoodSpot*> AllFoodSpot = //TODO

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
					UE_LOG(LogTemp, Warning, TEXT("Leave with a size of %d"), SpotsForPatrol.Num())
					return EBTNodeResult::Succeeded;
				}
			}*/
			
			BlackboardComponent->SetValueAsInt("HasARole", 1);
			return EBTNodeResult::Succeeded;
		}
	}

	
	return EBTNodeResult::Failed;
}

AActor* UBT_SelectSpotFood::SelectRandomFoodSpot(TArray<AFoodSpot*> ActorList)
{
	const int RandomIndex = FMath::FRandRange(0, ActorList.Num());
	UE_LOG(LogTemp, Warning, TEXT("Select rand : %d"), RandomIndex);
	return ActorList[RandomIndex];
}
