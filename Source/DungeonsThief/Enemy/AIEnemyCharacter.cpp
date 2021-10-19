// Fill out your copyright notice in the Description page of Project Settings.


#include "AIEnemyCharacter.h"


#include "AIEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DungeonsThief/Food/Food.h"
#include "Components/CapsuleComponent.h"
#include "DungeonsThief/Managers/AAnimationsHandler.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAIEnemyCharacter::AAIEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsulePlayerDetection = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerDetection"));
	CapsulePlayerDetection->SetupAttachment(GetRootComponent());
	CapsulePlayerDetection->InitCapsuleSize(20, 50);

	CapsulePlayerDetection->SetCollisionEnabled(ECollisionEnabled::NoCollision); 
	CapsulePlayerDetection->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CapsulePlayerDetection->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CapsulePlayerDetection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap); 
	
	BaseSpeed = 450.0f;

	bHasSeenPlayer = false;
	bIsInSight = false;
	bIsInWanderCooldown = false;

	WanderDelay = 3.0f;
	WanderCooldown = 0.0f;

	AnimationHandler = CreateDefaultSubobject<AAnimationsHandler>(TEXT("AnimationHandler"));
}

// Called when the game starts or when spawned
void AAIEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	CapsulePlayerDetection->OnComponentBeginOverlap.AddDynamic(this, &AAIEnemyCharacter::OnPlayerDetectionOverlapBegin);
	
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
	SetRandomMesh();

	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GameModeBase is null"));
		return;
	}

	//Bind to the gamemode events
	MyGameMode = Cast<AMyGameMode>(GameModeBase);
	if (MyGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameMode is null"));
		return;
	}
	
	MyGameMode->OnGameWin.AddDynamic(this, &AAIEnemyCharacter::EnemyLooseGame);
	MyGameMode->OnGameLoose.AddDynamic(this, &AAIEnemyCharacter::EnemyWinGame);

	OnDestroyed.AddDynamic(this, &AAIEnemyCharacter::OnDestoyingBehaviour);
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
			bIsInWanderCooldown = false;
			bHasSeenPlayer = false;
		}		
	}
}

void AAIEnemyCharacter::StopMovement()
{
	AAIEnemyController* EnemyController = Cast<AAIEnemyController>(GetController());

	if (EnemyController)
	{
		EnemyController->StopMovement();
		EnemyController->StopBehaviouTree();
	}
}

void AAIEnemyCharacter::OnDestoyingBehaviour(AActor* Act)
{
	if (MyGameMode == nullptr)
	{
		return;
	}

	MyGameMode->OnGameWin.RemoveDynamic(this, &AAIEnemyCharacter::EnemyLooseGame);
	MyGameMode->OnGameLoose.RemoveDynamic(this, &AAIEnemyCharacter::EnemyWinGame);
}

void AAIEnemyCharacter::EnemyWinGame()
{
	if (AnimationHandler && WinMontage)
	{
		StopMovement();
		
		AnimationHandler->PlayAnimation(this, WinMontage);
	}
}

void AAIEnemyCharacter::EnemyLooseGame()
{
	if (AnimationHandler && LooseMontage)
	{
		StopMovement();

		AnimationHandler->PlayAnimation(this, LooseMontage);
	}
}

/**
 * @brief Pick random mesh from an array to set the UStaticMeshComponent mesh
 */
void AAIEnemyCharacter::SetRandomMesh()
{
	//Choose random index
	int Random = FMath::FRandRange(0,MeshArray.Num());
	GetMesh()->SetSkeletalMesh(MeshArray[Random]);
	
	Random = FMath::FRandRange(0,MaterialArray.Num());
	GetMesh()->SetMaterial(0, MaterialArray[Random]);
	
}

void AAIEnemyCharacter::OnPlayerDetectionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("OtherActor is null"));
		return;
	}
	
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter == nullptr)
	{
		//Overlap actor isn't the Player
		return;
	}

	if (MyGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameMode is null"));
		return;
	}
	
	MyGameMode->LooseGame();
}




