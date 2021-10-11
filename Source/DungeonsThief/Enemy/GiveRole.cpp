// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/GiveRole.h"

#include "AIEnemyCharacter.h"
#include "AIEnemyController.h"
#include "DungeonsThief/Food/Food.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UGiveRole::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if(AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			TArray<AActor*> AllFood;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFood::StaticClass(), AllFood);
			//2 is a temporary number for test can be changed
			if(AllFood.Num() < 2)
			{
				UE_LOG(LogTemp, Warning, TEXT("CarryFood"))
				AICharacter->CarryNewFood();
			}else
			{
				AICharacter->SetIsAPatrol(true);
				AICharacter->ChooseFoodSpot();
			}


			AICharacter->SetHasARole(true);
			return EBTNodeResult::Succeeded;
		}
	}

	
	return EBTNodeResult::Failed;

	
}
