// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreManager.h"
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

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIEnemyCharacter::StaticClass(), EnemiesInLevel);

	for (AActor* Enemy : EnemiesInLevel)
	{
		if (Enemy)
		{
			AAIEnemyCharacter* EnemyCharacter = Cast<AAIEnemyCharacter>(Enemy);

			if (EnemyCharacter)
			{
				EnemyCharacter->LooseGame();
				AAIEnemyController* Controller = Cast<AAIEnemyController>(EnemyCharacter->GetController());

				if (Controller)
				{
					Controller->StopMovement();
				}				
			}
		}
	}
}

void AScoreManager::PlayerLoose()
{
	if (Player)
	{
		Player->SetCanMove(false);
		Player->LooseGame();		
	}
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIEnemyCharacter::StaticClass(), EnemiesInLevel);

	for (AActor* Enemy : EnemiesInLevel)
	{
		if (Enemy)
		{
			AAIEnemyCharacter* EnemyCharacter = Cast<AAIEnemyCharacter>(Enemy);

			if (EnemyCharacter)
			{
				EnemyCharacter->WinGame();
				AAIEnemyController* Controller = Cast<AAIEnemyController>(EnemyCharacter->GetController());

				if (Controller)
				{
					Controller->StopMovement();
				}	
			}
		}
	}
}
