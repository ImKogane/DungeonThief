// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_NPCTargetPointSelection.h"

#include "AIEnemyCharacter.h"
#include "AIEnemyController.h"
#include "NPCTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBT_NPCTargetPointSelection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
	
	if (AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		// If the AI has seen the player we don't want it to keep patrolling
		if (AICharacter)
		{
			if (AICharacter->GetHasSeenPlayer())
			{
				return EBTNodeResult::Failed; 
			}
		}
		
		//Get the Blackboard component and the Current Point of the NPC
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();
		ANPCTargetPoint* CurrentPoint = Cast<ANPCTargetPoint>(BlackboardComponent->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailableTargetsPoints = AIController->GetAvailableTargetPoints();

		int32 RandomIndex;

		//We store the possible next target Point
		ANPCTargetPoint* NextTargetPoint = nullptr;

		do
		{
			RandomIndex = FMath::RandRange(0, AvailableTargetsPoints.Num() - 1);
			NextTargetPoint = Cast<ANPCTargetPoint>(AvailableTargetsPoints[RandomIndex]);
		}
		while (CurrentPoint == NextTargetPoint);

		// Update the next location in the blackboard so the NPC can move to the next Blackboard value
		BlackboardComponent->SetValueAsObject("LocationToGo", NextTargetPoint);

		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
