// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Food.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AFood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Global")
	TArray<class UStaticMesh*> FoodArray;

	UPROPERTY(EditDefaultsOnly, Category="Global")
	int FoodPoints = 1;
	
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* FoodMesh;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleAnywhere, Category="SuperFood")
	bool IsSuperFood;

	UPROPERTY(EditDefaultsOnly, Category="SuperFood")
	class UStaticMesh* SuperFoodMesh;
	
	UPROPERTY(VisibleAnywhere, Category="SuperFood")
	int SuperFoodRate = 10;

	UPROPERTY(VisibleAnywhere, Category="SuperFood")
	float SpeedReduction = 0.5;
	
			
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetRandomMesh();
	void BecomeSuperFood();

	UFUNCTION()
	void OnBoxOverlapBegin( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnBoxOverlapEnd( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
	
public:	
	// Called every frame

	UFUNCTION()
	void BeTake();
	void BeDrop();

	FORCEINLINE UStaticMeshComponent* GetMeshComponent() { return FoodMesh; } 
	FORCEINLINE bool GetIsSuperFood() { return IsSuperFood; } 
	FORCEINLINE int GetFoodPoints	() { return FoodPoints; } 
	FORCEINLINE float GetSpeedReduction	() { return SpeedReduction; } 
	
	virtual void Tick(float DeltaTime) override;

};
