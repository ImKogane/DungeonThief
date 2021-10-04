// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>("FoodMesh");

}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{

	Super::BeginPlay();
	SetRandomMesh();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/**
 * @brief Pick random mesh from an array to set the UStaticMeshComponent mesh
 */
void AFood::SetRandomMesh()
{
    //Choose random index
	int random = FMath::FRandRange(0,9);
	
	
	if(FoodMesh != nullptr)
	{
		FoodMesh->SetStaticMesh(FoodArray[random]);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("NullPTR désolé !"));
	}
	
}
