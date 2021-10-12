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
	
	FORCEINLINE bool GetIsInSight() {return bIsInSight;}
	FORCEINLINE void SetIsInSight(bool value) {bIsInSight = value;}

	FORCEINLINE void ResetSetWanderCooldown()
	{
		WanderCooldown = WanderDelay;
		bHasSeenPlayer = false;
	}
	
	FORCEINLINE bool IsInWanderCooldown() { return WanderCooldown > 0; }

	FORCEINLINE bool GetHasARole() {return bHasARole;}
	FORCEINLINE void SetHasARole(bool value) {bHasARole = value;}

	FORCEINLINE bool GetIsAPatrol() {return bIsAPatrol;}
	FORCEINLINE void SetIsAPatrol(bool value) {bIsAPatrol = value;}
	
	FORCEINLINE bool GetHadFood() {return bHadFood;}
	FORCEINLINE void SetHadFood(bool value) {bHadFood = value;}
	
	FORCEINLINE bool GetFollowedAPlayer() {return bFollowedAPlayer;}
	FORCEINLINE void SetFollowedAPlayer(bool value) {bFollowedAPlayer = value;}

	FORCEINLINE TSubclassOf<class AFood> GetFoodActorBP(){return FoodActorBP;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bHasSeenPlayer;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bIsInSight;


	//Lionel Part (pour me souvenir)
	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bIsAPatrol;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bHadFood;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bFollowedAPlayer;
	
	//Has the AI a role ? : Patrol or CarryFood
	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bHasARole;
	//End

	
	float WanderDelay;
	float WanderCooldown;


	UPROPERTY(EditAnywhere, Category = "Food")
	TSubclassOf<class AFood> FoodActorBP;

	


	class AAnimationsHandler* AnimationHandler;

	UPROPERTY(EditAnywhere, Category = "Animations")
	class UAnimMontage* WinMontage;
	
	UPROPERTY(EditAnywhere, Category = "Animations")
	class UAnimMontage* LooseMontage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//used only if the AI is a patrol
	UPROPERTY(VisibleAnywhere, Category = "AI")
	TArray<AFoodSpot*> PatrolSpot;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void WinGame();

	void LooseGame();

protected:

	void ProcessWanderCooldown(float DeltaTime);
};
