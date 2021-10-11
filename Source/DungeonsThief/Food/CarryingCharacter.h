// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodSpot.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "CarryingCharacter.generated.h"

UCLASS()
class DUNGEONSTHIEF_API ACarryingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACarryingCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float BaseSpeed;
	
	UPROPERTY(VisibleAnywhere, Category = "Food")
	bool IsCarryFood;

	UPROPERTY(VisibleAnywhere, Category = "Other")
	class AActor* TempActor;
	
	UPROPERTY(VisibleAnywhere, Category = "Food")
	AActor* WornFood;

	UPROPERTY(VisibleAnywhere, Category = "FoodSpot")
	bool NearToFoodSpot;

	UPROPERTY(VisibleAnywhere, Category = "FoodSpot")
	AFoodSpot* SpotReference;
	

	UFUNCTION()
	void CarryItem();
	void PutItemOnSpot();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void InteractWithItem();
	
	FORCEINLINE void SetPlayerActor(AActor* NewActor) { TempActor = NewActor; }
	FORCEINLINE void SetSpeed(float NewSpeed) { GetCharacterMovement()->MaxWalkSpeed = NewSpeed; };
	
	FORCEINLINE void SetIsNearSpot(bool NewState){ NearToFoodSpot = NewState; }; 
	void SetSpotReference(AFoodSpot* Reference);

	FORCEINLINE bool GetIsCarryFood() { return IsCarryFood; }
	FORCEINLINE AActor* GetWornFood() { return WornFood; }
	FORCEINLINE AActor* GetPlayerTempActor() { return TempActor; }
	
	UFUNCTION()
	void DropItem();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
