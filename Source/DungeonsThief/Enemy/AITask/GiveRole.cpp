// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/GiveRole.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Food/Food.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UGiveRole::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if(AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();
			
			TArray<AActor*> AllFood;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFood::StaticClass(), AllFood);
			
			//2 is a temporary number for test can be changed
			if(AllFood.Num() >= 2)
			{
				uint8 ByteEnum = (uint8)EEnemyState::EES_Patrolling;
				BlackboardComponent->SetValueAsEnum("EnemyState", ByteEnum);
				AICharacter->SetIsAPatrol(true);
			}else
			{
				uint8 ByteEnum = (uint8)EEnemyState::EES_CarryFood;
				BlackboardComponent->SetValueAsEnum("EnemyState", ByteEnum);
			}


			AICharacter->SetHasARole(true);
			return EBTNodeResult::Succeeded;
		}
	}

	
	return EBTNodeResult::Failed;

	
}
