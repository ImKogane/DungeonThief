// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyGameMode.h"

#include "MyGameInstance.h"
#include "MyGameState.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Managers/SpawnEnemyManager.h"

void AMyGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
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
}

void AMyGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	
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

	if (MyGameState->HasPlayerWin() && MyGameInstance->GetGameplayMode() == EGameplayMode::EGM_NormalMode)
	{
		WinGame();
	}
}
