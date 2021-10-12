// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FoodManager.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AFoodManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFoodManager();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Food System")
	TArray<class AFoodSpot*> SpotsArray;

	UPROPERTY(EditAnywhere, Category="Food System")
	TSubclassOf<class AFood> FoodActor;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//return all spot in game
	FORCEINLINE TArray<class AFoodSpot*> getAllSpotInGame() { return SpotsArray;}
	FORCEINLINE TSubclassOf<class AFood> getBPFoodActor() {return FoodActor;}
	
	class AFood* SpawnFood(FVector SpawnLocation);
	
};
