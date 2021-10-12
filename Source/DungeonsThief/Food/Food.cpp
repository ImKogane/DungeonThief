// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>("FoodMesh");

	CollisionBox = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	CollisionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetupAttachment(FoodMesh);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFood::OnBoxOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AFood::OnBoxOverlapEnd);

}

void AFood::BeTake()
{
	UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetActorLocation());
	FoodMesh->SetCollisionProfileName(TEXT("OverlapAll"));
}

void AFood::BeDrop()
{
	FoodMesh->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	//FoodMesh->SetSimulatePhysics(true);
}


// Called when the game starts or when spawned
void AFood::BeginPlay()
{

	Super::BeginPlay();
	SetRandomMesh();

	BecomeSuperFood();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


/**
 * @brief Pick random mesh from an array to set the UStaticMeshComponent mesh
 */
void AFood::SetRandomMesh()
{
    //Choose random index
	int random = FMath::FRandRange(0,FoodArray.Num());
	
	
	if(FoodMesh != nullptr)
	{
		FoodMesh->SetStaticMesh(FoodArray[random]);
	}
	
}

void AFood::BecomeSuperFood()
{

	int randomIndex = FMath::FRandRange(0,SuperFoodRate+1);

	if(randomIndex == 5)
	{
		FoodPoints = 2;
		SpeedReduction = 0.25;
		FoodMesh->SetStaticMesh(SuperFoodMesh);
		IsSuperFood = true;
	}
	
}

void AFood::OnBoxOverlapBegin( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	
	if(Player != nullptr)
	{
		Player->SetPlayerActor(this);
	}
}

void AFood::OnBoxOverlapEnd( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	
	if(Player != nullptr)
	{
		Player->SetPlayerActor(nullptr);
	}
}
