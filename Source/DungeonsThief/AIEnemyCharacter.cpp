// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAIEnemyCharacter::AAIEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bHasSeenPlayer = false;
}

// Called when the game starts or when spawned
void AAIEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = 450.f;	
}

// Called every frame
void AAIEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

