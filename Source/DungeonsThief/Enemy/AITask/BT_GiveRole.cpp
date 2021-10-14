// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_GiveRole.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Managers/FoodManager.h"

EBTNodeResult::Type UBT_GiveRole::CodeToExecute()
{
	AFoodManager* FoodManager = Cast<AFoodManager>(BlackboardComponent->GetValueAsObject("FoodManager"));

	if (FoodManager && !FoodManager->GlobalWaitTest)
	{
		FoodManager->GlobalWaitTest = true;
		const int NumberOfFoodInWorld = FoodManager->getAllFoodInWorld().Num();
		if(NumberOfFoodInWorld >= FoodManager->getAllSpotInGame().Num())
		{
			uint8 ByteEnum = (uint8)EEnemyState::EES_Patrolling;
			BlackboardComponent->SetValueAsEnum("EnemyState", ByteEnum);
		}else
		{
			uint8 ByteEnum = (uint8)EEnemyState::EES_CarryFood;
			BlackboardComponent->SetValueAsEnum("EnemyState", ByteEnum);
			AIController->SetEnemyState(EEnemyState::EES_CarryFood);
		}
		return EBTNodeResult::Succeeded;
	}
			
	UE_LOG(LogTemp, Warning, TEXT("Waiting %s"), *AICharacter->GetName())
	return EBTNodeResult::Failed;
}
