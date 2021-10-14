// Fill out your copyright notice in the Description page of Project Settings.


#include "CarryingCharacter.h"
#include "FoodSpot.h"
#include "Food.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACarryingCharacter::ACarryingCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACarryingCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACarryingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(FoodCarriedActor != nullptr)
	{
		FoodCarriedActor->SetActorLocation(this->GetActorLocation());
	}
}

// Called to bind functionality to input
void ACarryingCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/**
* @brief Pick random mesh from an array to set the UStaticMeshComponent mesh
*/
void ACarryingCharacter::InteractWithItem()
{
	if(NearFoodActor != nullptr)
	{
		AFood* TempFood = Cast<AFood>(NearFoodActor);
		if(TempFood != nullptr)
		{
			if(IsCarryFood == false)
			{
				CarryItem();
				TempFood->BeTake();			
			}
			else
			{
				DropItem();
				TempFood->BeDrop();
			}			
		}
	}
	else
	{
		if(NearToFoodSpot == true)
		{
			if(IsCarryFood == true)
			{
				PutItemOnSpot();	
			}
		}
		else
		{
			DropItem();
		}
	}
}



/**
* @brief Put item (food) on a nearest spot
*/
void ACarryingCharacter::PutItemOnSpot()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	FoodCarriedActor->SetActorLocation(SpotReference->GetSpawnPoint()->GetComponentLocation());
	NearFoodActor = FoodCarriedActor;
	AFood* ModifyFoodData = Cast<AFood>(NearFoodActor);
	ModifyFoodData->SetIsOnSpot(true);
	FoodCarriedActor = nullptr;
	IsCarryFood = false;
}

/**
* @brief Set player speed in depend of it's worn item
*/
void ACarryingCharacter::SetPlayerSpeed()
{
	if(IsCarryFood)
	{
		AFood* TempFood = Cast<AFood>(FoodCarriedActor);

		if(TempFood !=nullptr)
		{
			GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * TempFood->GetSpeedReduction();
			
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * 0.5;
		}
		
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	}
}

void ACarryingCharacter::SetSpotReference(AFoodSpot* Reference)
{
	if(Reference != nullptr)
	{
		SpotReference = Reference;
	}
	else
	{
		SpotReference = nullptr;
	}
}

/**
* @brief Event when player carry item
*/
void ACarryingCharacter::CarryItem()
{
	if(IsCarryFood == false)
	{
		IsCarryFood = true;

		if(NearFoodActor != nullptr)
		{
			FoodCarriedActor = NearFoodActor;
			AFood* ModifyFoodData = Cast<AFood>(FoodCarriedActor);
			ModifyFoodData->SetIsOnSpot(false);
			NearFoodActor = nullptr;
			SetPlayerSpeed();
			FoodCarriedActor->SetActorLocation(this->GetActorLocation());			
		}
	}
}

/**
* @brief Event when player drop item (on floor or on spot)
*/
void ACarryingCharacter::DropItem()
{
	if(IsCarryFood == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Drop item."));
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
		IsCarryFood = false;

		if(FoodCarriedActor != nullptr)
		{
			NearFoodActor = FoodCarriedActor;
			FoodCarriedActor = nullptr;
			IsCarryFood = false;
		}
			
	}
}

