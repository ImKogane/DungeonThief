// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "DungeonsThief/Food/FoodSpot.h"
#include "DungeonsThief/Food/Food.h"

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

	SpawnFood();
	
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
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NullPTR désolé !"));
	}	
}

void AGameManager::AddPoints(int PointsCount)
{
	Points += PointsCount;
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, TEXT("++"));

	if(Points >= 5)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("YOU WIN"));
	}
}
