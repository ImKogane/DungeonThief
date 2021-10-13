// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_CarryNewFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Food/Food.h"
#include "DungeonsThief/Managers/FoodManager.h"

EBTNodeResult::Type UBT_CarryNewFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if(AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();

			//A VOIR SI CA FONCTIONNE BIEN
			AFoodManager* FoodManager = Cast<AFoodManager>(BlackboardComponent->GetValueAsObject("FoodManager"));

			if (FoodManager)
			{
				AActor* FoodToCarry = FoodManager->SpawnFood(AICharacter->GetActorLocation());
				if(FoodToCarry)
				{
					AICharacter->SetPlayerActor(FoodToCarry);
					AICharacter->InteractWithItem();
					FoodManager->GlobalWaitTest = false;
					BlackboardComponent->SetValueAsObject("FoodCarrying", FoodToCarry);
					BlackboardComponent->SetValueAsInt("HasARole", 1);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
