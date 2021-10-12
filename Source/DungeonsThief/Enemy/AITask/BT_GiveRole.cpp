// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_GiveRole.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"

EBTNodeResult::Type UBT_GiveRole::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if(AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();

			//TODO Actualiser les nourritures présentes dans le World surement dans le FoodManager
			
			//2 is a temporary number for test can be changed
			if(2 >= 2)
			{
				uint8 ByteEnum = (uint8)EEnemyState::EES_Patrolling;
				BlackboardComponent->SetValueAsEnum("EnemyState", ByteEnum);
			}else
			{
				uint8 ByteEnum = (uint8)EEnemyState::EES_CarryFood;
				BlackboardComponent->SetValueAsEnum("EnemyState", ByteEnum);
				AIController->SetEnemyState(EEnemyState::EES_CarryFood);
			}
			
			return EBTNodeResult::Succeeded;
		}
	}

	
	return EBTNodeResult::Failed;

	
}
