// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIEnemyCharacter.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AAIEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIEnemyCharacter();
	
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviourTree;

	FORCEINLINE bool GetHasSeenPlayer() {return bHasSeenPlayer;}
	FORCEINLINE void SetHasSeenPlayer(bool value) {bHasSeenPlayer = value;}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	bool bHasSeenPlayer;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
