// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "FoodSpot.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AFoodSpot : public AActor
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this actor's properties
	AFoodSpot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* SpotMesh;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
