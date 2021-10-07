// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
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

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* CollisionBox;
	

	
	
			
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetRandomMesh();

	UFUNCTION()
		void OnBoxOverlapBegin( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnBoxOverlapEnd( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame

	UFUNCTION()
	void BeTake();
	void BeDrop();
	
	UStaticMeshComponent* GetMeshComponent();
	virtual void Tick(float DeltaTime) override;

};
