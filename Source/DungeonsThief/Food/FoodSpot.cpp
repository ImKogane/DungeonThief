// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodSpot.h"
#include "DungeonsThief/Player/MainCharacter.h"


// Sets default values
AFoodSpot::AFoodSpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
    RootComponent = SceneComponent;
    
    SpotMesh = CreateDefaultSubobject<UStaticMeshComponent>("Spot");
    SpotMesh->SetupAttachment(RootComponent);



	CollisionBox = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	CollisionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetupAttachment(SpotMesh);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFoodSpot::OnBoxOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AFoodSpot::OnBoxOverlapEnd);
	
	SpawnSceneComponent = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	SpawnSceneComponent->SetupAttachment(SpotMesh);
	
	
	
	
}

// Called when the game starts or when spawned
void AFoodSpot::BeginPlay()
{
	
	Super::BeginPlay();
	
}


// Called every frame
void AFoodSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFoodSpot::OnBoxOverlapBegin( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	
	if(Player != nullptr)
	{
		Player->SetSpotReference(this);
		Player->SetIsNearSpot(true);
	}
}

void AFoodSpot::OnBoxOverlapEnd( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	if(Player != nullptr)
	{
		Player->SetSpotReference(nullptr);
		Player->SetIsNearSpot(false);
	}
}

