// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_UpdatePlayerPosition.h"
#include "AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBT_UpdatePlayerPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		//Get the Blackboard component and the Current Point of the NPC
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		AAIEnemyCharacter* EnemyCharacter = AIController->GetAICharacter();
		
		if (PlayerPawn && EnemyCharacter)
		{
			AMainCharacter* PlayerLocation = Cast<AMainCharacter>(PlayerPawn);
			
			if (PlayerLocation && EnemyCharacter->GetHasSeenPlayer())
			{
				BlackboardComponent->SetValueAsObject("PlayerLocation", PlayerLocation);
				
				return EBTNodeResult::Succeeded;
			}						
		}
	}

	return EBTNodeResult::Failed;
}
