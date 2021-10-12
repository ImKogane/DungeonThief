// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "DungeonsThief/Food/FoodSpot.h"
#include "DungeonsThief/HUD/UI_MainClass.h"
#include "DungeonsThief/Food/Food.h"
#include "Enemy/AIEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(PlayerPawn);
		if (MainCharacter)
		{
			Player = MainCharacter;
		}
	}
	
	SpawnFood();
	
}

void AGameManager::PlayerWin()
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
			}
		}
	}

}

void AGameManager::PlayerLoose()
{
	if (Player)
	{
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
			}
		}
	}
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameManager::SpawnFood()
{	
	int RandomIndex = FMath::FRandRange(0, SpotsArray.Num());
	//FString Index = FString::FromInt(RandomIndex);
	AFoodSpot* tempSpot = SpotsArray[RandomIndex];

	if(tempSpot != nullptr)
	{
		//GetWorld()->SpawnActor<AFood>(FoodActor, tempSpot->GetActorLocation(), tempSpot->GetActorRotation());
		GetWorld()->SpawnActor<AFood>(FoodActor, tempSpot->GetSpawnPoint()->GetComponentLocation(), tempSpot->GetSpawnPoint()->GetComponentRotation());
	}	
}

void AGameManager::AddPoints(int PointsCount)
{
	Points += PointsCount;
	FString PointsA = FString::FromInt(PointsCount);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, PointsA);

	if (Points >= 5)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("YOU WIN"));
	}
	
}
