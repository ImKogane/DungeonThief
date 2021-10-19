// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyGameMode.h"
#include "MyGameState.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"


void AMyGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	
}

void AMyGameMode::InitGameState()
{
	Super::InitGameState();

	AMyGameState* CurrentGameState = GetGameState<AMyGameState>();
	UWorld* World = GetWorld();
	
	if (World == nullptr && CurrentGameState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("World or GameState are null"));
		return;
	}

	MyGameState = CurrentGameState;
	
	FoodManager = MyGameState->SpawnFoodManager();
	SpawnEnemyManager = MyGameState->SpawnEnemyManager();
}

void AMyGameMode::WinGame()
{
	if (OnGameWin.IsBound())
	{
		OnGameWin.Execute();
	}

	/*
	if (SpawnManager)
	{
		EnemiesInLevel = SpawnManager->GetEnemiesSpawned();
	}

	for (AAIEnemyCharacter* Enemy : EnemiesInLevel)
	{
		if (Enemy)
		{
		}
	}*/
}

void AMyGameMode::LooseGame()
{
	if (OnGameLoose.IsBound())
	{
		OnGameLoose.Execute();
	}

	/*if (SpawnManager)
	{
		EnemiesInLevel = SpawnManager->GetEnemiesSpawned();
	}
	
	for (AAIEnemyCharacter* Enemy : EnemiesInLevel)
	{
		if (Enemy)
		{
			Enemy->WinGame();	
		}
	}*/
}

void AMyGameMode::GainPoints(int Points)
{
	MyGameState->AddPlayerPoints(Points);
	
	if (OnGainPoints.IsBound())
	{
		OnGainPoints.Execute();
	}
}
