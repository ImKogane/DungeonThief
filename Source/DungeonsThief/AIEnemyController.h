// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AAIEnemyController();

	FORCEINLINE UBlackboardComponent* GetBlackBoardComponent() const { return BlackboardComponent; }
	FORCEINLINE TArray<AActor*> GetAvailableTargetPoints() { return NPCTargetPoints; }

protected:

	/* Reference to the Behavior Tree */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	/* BlackBoard reference */
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UBlackboardComponent* BlackboardComponent;

	/* Blackboard keys */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKey;

	TArray<AActor*> NPCTargetPoints;

protected:

	/* This function is called when the enemy is spawned */
	/* We'll initialize the blackboard and start the behaviour tree */
	virtual void OnPossess(APawn* InPawn) override;
};
