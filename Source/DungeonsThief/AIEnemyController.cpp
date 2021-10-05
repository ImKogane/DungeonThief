// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyController.h"
#include "AIEnemyCharacter.h"
#include "NPCTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

/*
 * Contructor of the class
 */
AAIEnemyController::AAIEnemyController()
{
	//Initialize BehaviourTreeComponent and BlackBoardComponent and keys

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourComponent"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	LocationToGoKey = "LocationToGo";
}

void AAIEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AAIEnemyCharacter* AIChar = Cast<AAIEnemyCharacter>(InPawn);

	if (AIChar)
	{
		//If the blackboard variable is valid, we initialize the current blackBoard of the behaviour tree
		if (AIChar->BehaviourTree->BlackboardAsset)
		{
			if (BlackboardComponent)
			{
				BlackboardComponent->InitializeBlackboard(*(AIChar->BehaviourTree->BlackboardAsset));
			}
		}

		//We get all the NPC point in the level
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCTargetPoint::StaticClass(), NPCTargetPoints);

		//Start the behaviour tree which coreesponds to the specific character
		BehaviorTreeComponent->StartTree(*AIChar->BehaviourTree);
	}
}



