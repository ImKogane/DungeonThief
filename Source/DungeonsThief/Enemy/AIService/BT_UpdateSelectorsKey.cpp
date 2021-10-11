// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AIService/BT_UpdateSelectorsKey.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"

void UBT_UpdateSelectorsKey::ScheduleNextTick(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ScheduleNextTick(OwnerComp, NodeMemory);
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if (AIController)
	{
		UBlackboardComponent* BlackboardComponent = AIController->GetBlackBoardComponent();
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		
		if(AICharacter)
		{
			//update key if the character has a role
			if(AICharacter->GetHasARole())
				BlackboardComponent->SetValueAsInt("HasARole", 1);
			else
				BlackboardComponent->SetValueAsInt("HasARole", 0);

			//update key if the character carryFood
			if(AICharacter->GetIsCarryFood())
				BlackboardComponent->SetValueAsInt("IsCarryFood", 1);
			else
				BlackboardComponent->SetValueAsInt("IsCarryFood", 0);

			//update key if the character was following a player
			if(AICharacter->GetFollowedAPlayer())
				BlackboardComponent->SetValueAsInt("FollowedAPlayer", 1);
			else
				BlackboardComponent->SetValueAsInt("FollowedAPlayer", 0);

			//update key if the character had food at a time befor droping it
			if(AICharacter->GetHadFood())
				BlackboardComponent->SetValueAsInt("HadFood", 1);
			else
				BlackboardComponent->SetValueAsInt("HadFood", 0);

			//update key if the character is a patrol
			if(AICharacter->GetIsAPatrol())
			{
				BlackboardComponent->SetValueAsInt("IsAPatrol", 1);
			}
			else
				BlackboardComponent->SetValueAsInt("IsAPatrol", 0);
			

			
		}
	}
}
