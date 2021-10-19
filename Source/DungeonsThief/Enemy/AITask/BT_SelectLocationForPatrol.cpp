// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Enemy/AITask/BT_SelectLocationForPatrol.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UBT_SelectLocationForPatrol::CodeToExecute()
{
	AFoodManager* FoodManager = Cast<AFoodManager>(BlackboardComponent->GetValueAsObject("FoodManager"));

	if(FoodManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("FoodManager not found"))
		return EBTNodeResult::Failed;
	}
	
	NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	
	FNavLocation RandPointOnNav;
	
	TArray<FVector> LocationsForPatrol;
	
	for (int i = 0; i < 2; i++)
	{
		do
		{
			UE_LOG(LogTemp, Warning, TEXT("Get Point"))
			NavSystem->GetRandomPoint(RandPointOnNav);
		}while (!NavSystem->ProjectPointToNavigation(RandPointOnNav.Location, RandPointOnNav));
		
		LocationsForPatrol.Add(RandPointOnNav.Location);
	}
	
	if(LocationsForPatrol.Num() == 2)
	{
		AICharacter->SetLocationsForPatrol(LocationsForPatrol);
		BlackboardComponent->SetValueAsInt("HasARole", 1);
		FoodManager->GlobalWaitAI = false;
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
