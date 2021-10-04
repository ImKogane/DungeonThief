// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Food.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AFood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

protected:


	UPROPERTY(EditDefaultsOnly)
		TArray<UStaticMesh*> FoodArray;
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* FoodMesh;
			
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetRandomMesh();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
