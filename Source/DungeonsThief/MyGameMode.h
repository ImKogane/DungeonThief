// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:	
	DECLARE_DYNAMIC_DELEGATE(FOnGameWin);	
	DECLARE_DYNAMIC_DELEGATE(FOnGameLoose);
	DECLARE_DYNAMIC_DELEGATE(FOnGainPoints);

	FOnGameWin OnGameWin;
	FOnGameLoose OnGameLoose;
	FOnGainPoints OnGainPoints;

	FORCEINLINE class AFoodManager* GetFoodManager() { return FoodManager; }
	FORCEINLINE class ASpawnEnemyManager* GetSpawnManager() { return SpawnEnemyManager; }

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Helpers")
	class AFoodManager* FoodManager;
	
	UPROPERTY(VisibleAnywhere, Category = "Helpers")
	class ASpawnEnemyManager* SpawnEnemyManager;

	class AMyGameState* MyGameState;

public:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void InitGameState() override;

	void WinGame();

	void LooseGame();
	
	void GainPoints(int Points);	
};
