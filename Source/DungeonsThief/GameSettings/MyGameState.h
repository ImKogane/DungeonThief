// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	EGS_Menu UMETA(DisplayName = "Menu"),
    EGS_Game UMETA(DisplayName = "Game"),

    EES_MAX UMETA(DisplayName = "Default")
};

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API AMyGameState : public AGameState
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Helpers")
	TSubclassOf<class AFoodManager> FoodManageBlueprint;
	
	UPROPERTY(EditAnywhere, Category = "Helpers")
	TSubclassOf<class ASpawnEnemyManager> SpawnEnemyManageBlueprint;
	
	TArray<class AAIEnemyCharacter*> EnemiesInLevel;

	UPROPERTY(VisibleAnywhere, Category = "Game State")
	EGameState CharacterGameState;
	
	UPROPERTY(VisibleAnywhere, Category = "Game State")
	int PlayerPoints;	
	
	UPROPERTY(EditAnywhere, Category = "Game State")
	int MaxPoints = 5;

public:

	//FORCEINLINE TSubclassOf<class AFoodManager> GetFoodManagerBlueprint() { return FoodManageBlueprint; } 
	//FORCEINLINE TSubclassOf<class ASpawnEnemyManager> GetSpawnManagerBlueprint() { return SpawnEnemyManageBlueprint; }

	FORCEINLINE EGameState GetGameState() { return CharacterGameState; }
	FORCEINLINE void SetGameState(EGameState NewState) { CharacterGameState = NewState; }

	FORCEINLINE int GetPlayerPoints() { return PlayerPoints; }
	FORCEINLINE void AddPlayerPoints(int PointsToAdd) { PlayerPoints += PointsToAdd; }

	FORCEINLINE float GetProgressionPercent() { return (float)PlayerPoints / (float)MaxPoints; }
	
    FORCEINLINE TArray<class AAIEnemyCharacter*> GetEnemiesInLevel() { return EnemiesInLevel; }
	FORCEINLINE void AddEnemiesInLevel(class AAIEnemyCharacter* EnemyToAdd) { EnemiesInLevel.Add(EnemyToAdd); }

	FORCEINLINE bool HasPlayerWin() {return PlayerPoints >= MaxPoints; }

	class AFoodManager* SpawnFoodManager();

	class ASpawnEnemyManager* SpawnEnemyManager();

};
