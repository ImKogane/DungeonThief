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

	FORCEINLINE void SetSpotsForPatrol(TArray<AFoodSpot*> Spots){ SpotsForPatrol = Spots; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bHasSeenPlayer;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bIsInSight;
	
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
