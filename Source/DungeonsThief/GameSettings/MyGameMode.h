// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameWin);	
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameLoose);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGainPoints);

UCLASS()
class DUNGEONSTHIEF_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	
	FOnGameWin OnGameWin;
	FOnGameLoose OnGameLoose;
	FOnGainPoints OnGainPoints;

	FORCEINLINE class AFoodManager* GetFoodManager() { return FoodManager; }
	FORCEINLINE class ASpawnEnemyManager* GetSpawnManager() { return SpawnEnemyManager; }

	FORCEINLINE void InitFoodManager(class AFoodManager* FM) { FoodManager = FM;};

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Helpers")
	class AFoodManager* FoodManager;
	
	UPROPERTY(VisibleAnywhere, Category = "Helpers")
	class ASpawnEnemyManager* SpawnEnemyManager;
	
	UPROPERTY(VisibleAnywhere, Category = "Helpers")
	class UMyGameInstance* MyGameInstance;

	class AMyGameState* MyGameState;

public:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	virtual void InitGameState() override;

	virtual void HandleMatchHasStarted() override;
	
	void WinGame();

	void LooseGame();
	
	void GainPoints(int Points);	
};
