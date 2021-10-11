// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/SelectSpotFood.h"

#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type USelectSpotFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIEnemyController* AIController = Cast<AAIEnemyController>(OwnerComp.GetAIOwner());

	if(AIController)
	{
		AAIEnemyCharacter* AICharacter = AIController->GetAICharacter();
		if(AICharacter)
		{
			TArray<AActor*> AllFoodSpot;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFoodSpot::StaticClass(), AllFoodSpot);
			if(AllFoodSpot.Num() >= 2)
			{
				for (int i = 0; i < 2; i++)
				{
					AFoodSpot* TempAct = Cast<AFoodSpot>(SelectRandomActor(AllFoodSpot));
					
					while(AICharacter->PatrolSpot.Contains(TempAct))
					{
						TempAct = Cast<AFoodSpot>(SelectRandomActor(AllFoodSpot));
					}
					AICharacter->PatrolSpot.Add(TempAct);
				}
				UE_LOG(LogTemp, Warning, TEXT("Leave with a size of %d"), AICharacter->PatrolSpot.Num())
				return EBTNodeResult::Succeeded;
			}
		}
	}

	
	return EBTNodeResult::Failed;
}

AActor* USelectSpotFood::SelectRandomActor(TArray<AActor*> ActorList)
{
	int RandomIndex = FMath::FRandRange(0, ActorList.Num());
	UE_LOG(LogTemp, Warning, TEXT("Select rand : %d"), RandomIndex);
	return ActorList[RandomIndex];
}
