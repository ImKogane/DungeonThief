// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:

	UFUNCTION()
	void SpawnFood();
			

	UPROPERTY(EditAnywhere, Category="Food System")
	TArray<class AFoodSpot*> SpotsArray;

	UPROPERTY(EditAnywhere, Category="Food System")
	TSubclassOf<class AFood> FoodActor;

	UPROPERTY(VisibleAnywhere, Category="Points System")
	int Points;	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AddPoints(int PointsCount);

};
