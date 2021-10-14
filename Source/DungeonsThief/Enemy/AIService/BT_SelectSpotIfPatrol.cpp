// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AIService/BT_SelectSpotIfPatrol.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"

void UBT_SelectSpotIfPatrol::ScheduleNextTick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ScheduleNextTick(OwnerComp, NodeMemory);

	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			
			UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();

			TArray<AFoodSpot*> SpotsForPatrol = AICharacter->GetSpotsForPatrol();
			if(SpotsForPatrol.Num() > 0)
			{
				BlackboardComponent->SetValueAsObject("SpotLocationToGo", SpotsForPatrol[0]);
			}else
				BlackboardComponent->ClearValue("SpotLocationToGo");
		}
	}
}
