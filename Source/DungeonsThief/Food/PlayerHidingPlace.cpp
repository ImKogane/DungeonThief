// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHidingPlace.h"
#include "DungeonsThief/Food/Food.h"
#include "DungeonsThief/Managers/FoodManager.h"
#include "DungeonsThief/Managers/ScoreManager.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerHidingPlace::APlayerHidingPlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this,&APlayerHidingPlace::OnBoxOverlapBegin);
	//CollisionBox->OnComponentEndOverlap.AddDynamic(this, &APlayerHidingPlace::OnBoxOverlapEnd);

}

// Called when the game starts or when spawned
void APlayerHidingPlace::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerHidingPlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerHidingPlace::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMainCharacter* Player = Cast<AMainCharacter>(OtherActor);
	if (Player != nullptr)
	{
		if (Player->GetIsCarryFood())
		{
			AFood* HeldFood = Cast<AFood>(Player->GetFoodCarried());

			if (HeldFood && ScoreManager)
			{
				ScoreManager->AddPoints(HeldFood->GetFoodPoints());
			}
			if(FoodManager)
				FoodManager->RemoveFoodFromWorldList(HeldFood);
			
			Player->DropItem();
			Player->GetPlayerNearFoodActor()->Destroy();
			Player->SetNearFoodActor(nullptr);
		}
	}	
}

