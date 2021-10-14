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

	FORCEINLINE void SetWanderCooldown()
	{
		if (!bIsInWanderCooldown)
		{
			WanderCooldown = WanderDelay;
			bIsInWanderCooldown = true;
		}
	}
	
	FORCEINLINE bool IsInWanderCooldown() { return bIsInWanderCooldown; }

	FORCEINLINE void SetSpotsForPatrol(TArray<AFoodSpot*> Spots){ SpotsForPatrol = Spots; }
	FORCEINLINE TArray<AFoodSpot*> GetSpotsForPatrol(){ return SpotsForPatrol; }
	FORCEINLINE void RemoveASpotForPatrol(AFoodSpot* SpotToRemove){ if(SpotsForPatrol.Contains(SpotToRemove)) SpotsForPatrol.Remove(SpotToRemove); }

	FORCEINLINE void AddAlreadyVisitedSpot(AFoodSpot* SpotVisited){ AlreadyVisitedSpot.Add(SpotVisited); }
	FORCEINLINE TArray<AFoodSpot*> GetAlreadyVisitedSpot(){ return AlreadyVisitedSpot; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bHasSeenPlayer;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bIsInSight;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bIsInWanderCooldown;
	
	float WanderDelay;
	float WanderCooldown;

	UPROPERTY(EditAnywhere, Category="Models")
	TArray<class USkeletalMesh*> MeshArray;
	
	UPROPERTY(EditAnywhere, Category="Models")
	TArray<class UMaterial*> MaterialArray;

	class AAnimationsHandler* AnimationHandler;

	UPROPERTY(EditAnywhere, Category = "Animations")
	class UAnimMontage* WinMontage;
	
	UPROPERTY(EditAnywhere, Category = "Animations")
	class UAnimMontage* LooseMontage;
	
	//used only if the AI is a patrol
	UPROPERTY(VisibleAnywhere, Category = "AI")
	TArray<AFoodSpot*> SpotsForPatrol;

	//used only if the AI carry food
	UPROPERTY(VisibleAnywhere, Category = "AI")
	TArray<class AFoodSpot*> AlreadyVisitedSpot;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
		
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void WinGame();

	void LooseGame();

	void SetRandomMesh();

protected:

	void ProcessWanderCooldown(float DeltaTime);
};
