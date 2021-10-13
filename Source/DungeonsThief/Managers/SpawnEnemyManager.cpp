// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Managers/SpawnEnemyManager.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Enemy/AIEnemyCharacter.h"
#include "DungeonsThief/Enemy/AIEnemyController.h"

// Sets default values
ASpawnEnemyManager::ASpawnEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DeleteEnemyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("DeleteEnemyBoxComponent"));
	DeleteEnemyBoxComponent->SetupAttachment(GetRootComponent());
	DeleteEnemyBoxComponent->InitBoxExtent(FVector(100, 10, 100));

	SpawnLocation = CreateDefaultSubobject<USphereComponent>(TEXT("SpawnLocation"));
	SpawnLocation->SetupAttachment(DeleteEnemyBoxComponent);
	SpawnLocation->InitSphereRadius(10);
	SpawnLocation->SetSimulatePhysics(false);
	
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

	//First spawn : 2 enemies are instanciated + wait 60s to instanciate a third one
	SpawnEnemy(60);	
}

// Called every frame
void ASpawnEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnEnemyManager::SetupEnemy(AAIEnemyCharacter* EnemyCharacter)
{
	if (EnemyCharacter)
	{
		AAIEnemyController* AIController = Cast<AAIEnemyController>(EnemyCharacter->GetController());

		if (AIController && FoodManager)
		{
			AIController->GetBlackBoardComponent()->SetValueAsObject("FoodManager", FoodManager);
		}
	}
}

void ASpawnEnemyManager::CreateEnemy()
{
	AAIEnemyCharacter* EnemyCharacter = GetWorld()->SpawnActor<AAIEnemyCharacter>(EnemyToSpawn, SpawnLocation->GetComponentLocation(), GetActorRotation());
	SetupEnemy(EnemyCharacter);
	EnemiesSpawned.Add(EnemyCharacter);
}

void ASpawnEnemyManager::SpawnEnemy(int Delay)
{
	FTimerHandle handle;
		
	if (bIsFirstSpawn)
	{
		bIsFirstSpawn = false;

		//spawned 2 ennemies
		for (int i = 0; i < 2; i++)
		{
			CreateEnemy();
		}
	}
	
	GetWorld()->GetTimerManager().SetTimer(handle, [this]()
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("SPAWNED"));
		CreateEnemy();
		
	}, Delay, false);
}

void ASpawnEnemyManager::DeleteBoxOnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AAIEnemyCharacter* AICharacter = Cast<AAIEnemyCharacter>(OtherActor);

		if (AICharacter)
		{
			//if an enemy touch this box collision, that means it's getting back to the spawner
			//we delete this one and remove it from the instanciated array
			EnemiesSpawned.Remove(AICharacter);
			AICharacter->Destroy();

			//check if the array is empty : true -> no more IA in the maps -> we need to instanciate one immediately
			if (EnemiesSpawned.Num() <= 0)
			{
				SpawnEnemy(0);
			}
			//else : we wait a random delay between 0 and 5s
			else
			{
				SpawnEnemy(FMath::FRandRange(MinSpawnDelay, MaxSpawnDelay));
			}
		}	
	}
}

void ASpawnEnemyManager::DeleteBoxOnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

