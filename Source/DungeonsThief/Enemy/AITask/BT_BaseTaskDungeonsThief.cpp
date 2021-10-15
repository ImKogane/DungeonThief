// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_BaseTaskDungeonsThief.h"

#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"

EBTNodeResult::Type UBT_BaseTaskDungeonsThief::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if(AIController ==  nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not found"))
		return EBTNodeResult::Failed;
	}
	
	AICharacter = AIController->GetAICharacter();
	BlackboardComponent = AIController->GetBlackBoardComponent();
	return CodeToExecute();
}

EBTNodeResult::Type UBT_BaseTaskDungeonsThief::CodeToExecute()
{
	return EBTNodeResult::Failed;
}

AFoodSpot* UBT_BaseTaskDungeonsThief::SelectRandomFoodSpot(TArray<AFoodSpot*> ActorList)
{
	const int RandomIndex = FMath::FRandRange(0, ActorList.Num());
	return ActorList[RandomIndex];
}
