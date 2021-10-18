// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreManager.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AScoreManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "SpawnManager")
	class ASpawnEnemyManager* SpawnManager;
	
	class AMainCharacter* Player;

	class AMyGameState* MyGameState;
	
	TArray<class AAIEnemyCharacter*> EnemiesInLevel;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
    void AddPoints(int PointsCount);

	// Play the win animation for the player and the defeat animation for all enemies spawned in the map
	void PlayerWin();

	//Play the win animation for all enemies spawned in the map and the defeat animation for the player
	void PlayerLoose();	
};
