// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnEnemyManager.generated.h"

/*
 *
 
Lorsque la partie commence, 2 IAs arrivent directement dans la salle en apportant des aliments.
Une 3ème IA arrive 1 minute après le début de la partie.
Lorsqu’une IA sort de la salle, une autre IA arrive entre 0 et 5s après.
Si à la sortie d’une IA aucune autre IA n’est présente dans la salle, alors l’IA qui devrait suivre arrive immédiatement.

 * 
 */

UCLASS()
class DUNGEONSTHIEF_API ASpawnEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UBoxComponent* DeleteEnemyBoxComponent;

	UPROPERTY(EditAnywhere, Category = "Spawn Enemy")
	TSubclassOf<class AAIEnemyCharacter> EnemyToSpawn;

	TArray<class AAIEnemyCharacter*> EnemiesSpawned;
	
	UPROPERTY(VisibleAnywhere, Category = "Spawn Enemy")
	int MinSpawnDelay;

	UPROPERTY(VisibleAnywhere, Category = "Spawn Enemy")
	int MaxSpawnDelay;

	int FirstSpawnDelay;

	bool bIsFirstSpawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	void SpawnEnemy();

	UFUNCTION()
    virtual void DeleteBoxOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	UFUNCTION()
    virtual void DeleteBoxOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
