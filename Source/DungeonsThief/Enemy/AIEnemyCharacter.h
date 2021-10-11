// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonsThief/Food/CarryingCharacter.h"
#include "AIEnemyCharacter.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AAIEnemyCharacter : public ACarryingCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemyCharacter();
	
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviourTree;

	FORCEINLINE bool GetHasSeenPlayer() {return bHasSeenPlayer;}
	FORCEINLINE void SetHasSeenPlayer(bool value) {bHasSeenPlayer = value;}
	
	FORCEINLINE bool GetHasARole() {return bHasARole;}
	FORCEINLINE void SetHasARole(bool value) {bHasARole = value;}

	FORCEINLINE bool GetIsInSight() {return bIsInSight;}
	FORCEINLINE void SetIsInSight(bool value) {bIsInSight = value;}

	FORCEINLINE void ResetSetWanderCooldown()
	{
		WanderCooldown = WanderDelay;
		bHasSeenPlayer = false;
	}
	
	FORCEINLINE bool IsInWanderCooldown() { return WanderCooldown > 0; }

	FORCEINLINE bool GetIsAPatrol() {return bIsAPatrol;}
	FORCEINLINE void SetIsAPatrol(bool value) {bIsAPatrol = value;}

	void CarryNewFood();

	void ChooseFoodSpot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bHasSeenPlayer;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bIsInSight;
	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bIsAPatrol;

	float WanderDelay;
	float WanderCooldown;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bHasARole;

	UPROPERTY(EditAnywhere, Category = "Food")
	TSubclassOf<class AFood> FoodActorBP;

	//used only if the AI is a patrol
	TArray<AFoodSpot*> PatrolSpot;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	void ProcessWanderCooldown(float DeltaTime);
};
