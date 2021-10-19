// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AIService/BT_SelectSpotIfPatrol.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"

void UBT_SelectSpotIfPatrol::ScheduleNextTick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ScheduleNextTick(OwnerComp, NodeMemory);

	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (AIController == nullptr)
	{
		return;
	}
	UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();
	
	AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();		
	TArray<FVector> LocationsForPatrol = AICharacter->GetLocationsForPatrol();
	
	if(LocationsForPatrol.Num() == 0)
	{
		BlackboardComponent->ClearValue("LocationForPatrol");
		return;
	}

	BlackboardComponent->SetValueAsVector("LocationForPatrol", LocationsForPatrol[0]);
}
