// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/HasARole.h"

#include "AIEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"

void UHasARole::ScheduleNextTick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ScheduleNextTick(OwnerComp, NodeMemory);

	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		
		if(AICharacter)
		{
			if(AICharacter->GetHasARole())
				BlackboardComponent->SetValueAsInt("HasARole", 1);
			else
				BlackboardComponent->SetValueAsInt("HasARole", 0);
		}
	}
}
