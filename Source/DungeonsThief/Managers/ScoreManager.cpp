// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManager.h"


#include "SpawnEnemyManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "Engine/World.h"

// Sets default values
AScoreManager::AScoreManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScoreManager::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void AScoreManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScoreManager::AddPoints(int PointsCount)
{
	Points += PointsCount;
	FString PointsA = FString::FromInt(PointsCount);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, PointsA);

	if (Points >= 5)
	{
		PlayerWin();
	}
}

void AScoreManager::PlayerWin()
{
	if (Player)
	{
		Player->WinGame();		
	}

	if (SpawnManager)
	{
		EnemiesInLevel = SpawnManager->GetEnemiesSpawned();
	}

	for (AAIEnemyCharacter* Enemy : EnemiesInLevel)
	{
		if (Enemy)
		{
			Enemy->LooseGame();
		}
	}
}

void AScoreManager::PlayerLoose()
{
	if (Player)
	{
		Player->LooseGame();		
	}

	if (SpawnManager)
	{
		EnemiesInLevel = SpawnManager->GetEnemiesSpawned();
	}
	
	for (AAIEnemyCharacter* Enemy : EnemiesInLevel)
	{
		if (Enemy)
		{
			Enemy->WinGame();	
		}
	}
}
