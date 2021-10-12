// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_CarryNewFood.h"

#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Food/Food.h"

EBTNodeResult::Type UBT_CarryNewFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if(AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			
			AActor* TempActor = GetWorld()->SpawnActor<AFood>(AICharacter->GetFoodActorBP(), AICharacter->GetActorLocation(), AICharacter->GetActorRotation());
			if(TempActor)
			{
				AICharacter->SetPlayerActor(TempActor);
				AICharacter->InteractWithItem();
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
