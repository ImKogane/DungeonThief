// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/BT_UpdatePlayerDirection.h"
#include "AIEnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"

EBTNodeResult::Type UBT_UpdatePlayerDirection::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());
    
    if (AIController)
    {
    	UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();

    	AAIEnemyCharacter* EnemyCharacter = AIController->GetAICharacter();

    	if (EnemyCharacter)
    	{
    		//We get the actual target (the player) set in the blackboard
    		AMainCharacter* MainChar = Cast<AMainCharacter>(BlackboardComponent->GetValueAsObject("PlayerLocation"));

    		if (MainChar)
    		{
    			//We get the player direction in order to know in which direction the AI should wander
    			FVector PlayerDirection = MainChar->GetActorForwardVector();
				FVector LastPlayerPosition = MainChar->GetActorLocation();

    			//We just add the direction to the last player position to set a point the AI should reach
    			//(x 1000 is there to have a position far enough away so that the enemy can walk during his 3 seconds of wander)  
    			FVector WanderingPosition = LastPlayerPosition + PlayerDirection * 1000.0f;

    			BlackboardComponent->SetValueAsVector("LastPlayerPosition", WanderingPosition);
    			return EBTNodeResult::Succeeded;
    		}
    	}
    }

	return EBTNodeResult::Failed;
}