// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_DropFood.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"

EBTNodeResult::Type UBT_DropFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if(AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();

			AICharacter->InteractWithItem();
			
			UObject* StoreFood = BlackboardComponent->GetValueAsObject("FoodCarrying");
			BlackboardComponent->SetValueAsObject("HadFood", StoreFood);
			BlackboardComponent->ClearValue("FoodCarrying");
			
			
			return EBTNodeResult::Failed;
		}
	}

	return EBTNodeResult::Failed;
}
