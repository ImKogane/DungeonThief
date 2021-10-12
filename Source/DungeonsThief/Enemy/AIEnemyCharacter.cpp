// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyCharacter.h"
#include "DungeonsThief/AAnimationsHandler.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAIEnemyCharacter::AAIEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bHasSeenPlayer = false;
	bIsInSight = false;

	WanderDelay = 3.0f;
	WanderCooldown = 0.0f;

	AnimationHandler = CreateDefaultSubobject<AAnimationsHandler>(TEXT("AnimationHandler"));
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

	ProcessWanderCooldown(DeltaTime);
}

// Called to bind functionality to input
void AAIEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAIEnemyCharacter::ProcessWanderCooldown(float DeltaTime)
{
	if (WanderCooldown > 0.0f)
	{
		WanderCooldown -= DeltaTime;

		if (WanderCooldown <= 0.0f) //Cooldown has ended
		{
			WanderCooldown = 0.0f;			
		}		
	}
}

void AAIEnemyCharacter::WinGame()
{
	if (AnimationHandler && WinMontage)
	{
		AnimationHandler->PlayAnimation(this, WinMontage);
	}
}

void AAIEnemyCharacter::LooseGame()
{
	if (AnimationHandler && LooseMontage)
	{
		AnimationHandler->PlayAnimation(this, LooseMontage);
	}
}



