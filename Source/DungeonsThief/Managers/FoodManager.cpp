// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodManager.h"
#include "DungeonsThief/Food/Food.h"
#include "DungeonsThief/Food/FoodSpot.h"

// Sets default values
AFoodManager::AFoodManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFoodManager::BeginPlay()
{
	Super::BeginPlay();

	int RandomIndex = FMath::FRandRange(0, SpotsArray.Num() - 1);

	AFoodSpot* FoodSpot = SpotsArray[RandomIndex];
	if (FoodSpot)
	{
		SpawnFood(FoodSpot->GetSpawnPoint()->GetComponentLocation());	
	}
}

// Called every frame
void AFoodManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AFood* AFoodManager::SpawnFood(FVector SpawnLocation)
{
	return GetWorld()->SpawnActor<AFood>(FoodActor, SpawnLocation, GetActorRotation());
}

