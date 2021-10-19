// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyGameMode.h"
#include "MyGameState.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"

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
}

void AMyGameMode::HandleMatchHasStarted()
{	
	SpawnEnemyManager = MyGameState->SpawnEnemyManager();
}

void AMyGameMode::WinGame()
{
	if (OnGameWin.IsBound())
	{
		OnGameWin.Broadcast();
	}
}

void AMyGameMode::LooseGame()
{
	if (OnGameLoose.IsBound())
	{
		UE_LOG(LogTemp, Warning, TEXT("GAME LOOSE"));
		OnGameLoose.Broadcast();
	}
}

void AMyGameMode::GainPoints(int Points)
{
	MyGameState->AddPlayerPoints(Points);
	
	if (OnGainPoints.IsBound())
	{
		OnGainPoints.Broadcast();
	}

	if (MyGameState->HasPlayerWin())
	{
		WinGame();
	}
}
