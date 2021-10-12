// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Managers/SpawnEnemyManager.h"
#include "Components/BoxComponent.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"

// Sets default values
ASpawnEnemyManager::ASpawnEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeleteEnemyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("DeleteEnemyBoxComponent"));
	DeleteEnemyBoxComponent->SetupAttachment(GetRootComponent());
	DeleteEnemyBoxComponent->InitBoxExtent(FVector(100, 10, 100));
	
	MinSpawnDelay = 0;
	MaxSpawnDelay = 5;
	
	FirstSpawnDelay = 60;

	bIsFirstSpawn = true;
}

// Called when the game starts or when spawned
void ASpawnEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	DeleteEnemyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpawnEnemyManager::DeleteBoxOnOverlapBegin);
	DeleteEnemyBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ASpawnEnemyManager::DeleteBoxOnOverlapEnd);
	
	SpawnEnemy();	
}

// Called every frame
void ASpawnEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnEnemyManager::SpawnEnemy()
{
	FTimerHandle handle;
	
	if (bIsFirstSpawn)
	{
		EnemiesSpawned.Add(GetWorld()->SpawnActor<AAIEnemyCharacter>(EnemyToSpawn, GetActorLocation(), GetActorRotation()));
		EnemiesSpawned.Add(GetWorld()->SpawnActor<AAIEnemyCharacter>(EnemyToSpawn, GetActorLocation(), GetActorRotation()));
	}
	
	float SpawnDelay = bIsFirstSpawn ? FirstSpawnDelay : FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);
	
	GetWorld()->GetTimerManager().SetTimer(handle, [this]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SPAWNED"));
	}, SpawnDelay, true);
}

void ASpawnEnemyManager::DeleteBoxOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AAIEnemyCharacter* AICharacter = Cast<AAIEnemyCharacter>(OtherActor);

		if (AICharacter)
		{
			EnemiesSpawned.Remove(AICharacter);
			AICharacter->Destroy();
		}
	}
}

void ASpawnEnemyManager::DeleteBoxOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

