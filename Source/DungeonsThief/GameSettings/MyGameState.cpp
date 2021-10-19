// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"

AFoodManager* AMyGameState::SpawnFoodManager()
{
	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		return nullptr;
	}

	return World->SpawnActor<AFoodManager>(FoodManageBlueprint, FVector(0,0,0), FRotator(0,0,0));
}

ASpawnEnemyManager* AMyGameState::SpawnEnemyManager()
{
	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		return nullptr;
	}

	//Location used in the MAIN LEVEL
	return World->SpawnActor<ASpawnEnemyManager>(SpawnEnemyManageBlueprint, FVector(-4817,-11436,930), FRotator(0,-90,0));
}
