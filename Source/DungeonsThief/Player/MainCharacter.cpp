// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "MainCharacterController.h"
#include "DungeonsThief/Managers/AAnimationsHandler.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"


class AMyGameMode;
// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera Boom Creation
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true; //Rotation base on the character controller

	//Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// Attach the camera to the end of the camera boom  
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
	
	BaseTurnRate = 65.0f;
	BaseLookupRate = 65.0f;

	//Don't rotate when the controller rotate (let that just affect the camera
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	//Character Movement configuration
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f); // at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = .2f;

	BaseSpeed = GetCharacterMovement()->MaxWalkSpeed;
	CrouchSpeed = BaseSpeed/2;

	MaxZoom = 600.0f;
	MinZoom = 200.0f;

	AnimationHandler = CreateDefaultSubobject<AAnimationsHandler>(TEXT("AnimationHandler"));

	bCanMove = true;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	MainCharacterController = Cast<AMainCharacterController>(GetController());
	
	//set where the camera is looking at
	CameraBoom->SetRelativeLocation(FVector(0,0,60));

	//Choose random index
	int Random = FMath::FRandRange(0,PlayableCharacters.Num());
	DefinePlayerCharacter(Random);

	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * SpeedBonus;

	//CurrentHitMesh = nullptr;
	//CurrentHitObjectMaterial = nullptr;
	
	//Bind method with the GameMode
	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase == nullptr)
	{
		return;
	}

	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameModeBase);
	if (MyGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MyGameMode is null"));
		return;
	}

	MyGameMode->OnGameWin.AddDynamic(this, &AMainCharacter::WinGame);
	MyGameMode->OnGameLoose.AddDynamic(this, &AMainCharacter::LooseGame);

}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ChangeObjectTransparency();
}

/*
 * Setup player inputs with custom functions
 */
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookupRate);

	PlayerInputComponent->BindAxis("ScrollCamera", this, &AMainCharacter::ScrollInOut);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::InteractWithItem);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharacter::CrouchPlayer);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainCharacter::UnCrouchPlayer);
	
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMainCharacter::SetGamePause);
}


//////////////////// PLAYER MOVEMENT ////////////////////
#pragma region Player movement

/*
 * Move the character in the forward or backward direction
 */
void AMainCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f && bCanMove)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::CrouchPlayer()
{
	if(IsCrouch == false && IsCarryFood == false)
	{
		Crouch();
		GetCharacterMovement()->MaxWalkSpeed = (BaseSpeed/1.75) * CrouchSpeedBonus;
		IsCrouch = true;
		GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}

}



void AMainCharacter::UnCrouchPlayer()
{
	if(IsCrouch == true)
	{
		UnCrouch();
		SetPlayerSpeed();
		IsCrouch = false;
	}
}



/*
 * Move the character in the right or left direction
 */
void AMainCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f && bCanMove)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
#pragma endregion 


//////////////////// CAMERA SYSTEM ////////////////////
#pragma region Camera System

	void AMainCharacter::TurnAtRate(float Rate)
	{
		if (bCanMove)
		{
			AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
		}
	}

	void AMainCharacter::LookupRate(float Rate)
	{
		if (bCanMove)
		{
			AddControllerPitchInput(Rate * BaseLookupRate * GetWorld()->GetDeltaSeconds());
		}
	}

	void AMainCharacter::ScrollInOut(float Value)
	{
		if(Value != 0.0f && bCanMove)
		{
			UE_LOG(LogTemp, Warning, TEXT("Je scroll"))
			
			float CurrentArmLenght = CameraBoom->TargetArmLength + Value;
			
			if(CurrentArmLenght < MaxZoom && CurrentArmLenght > MinZoom)
			{
				CameraBoom->TargetArmLength += Value;
			}
		}
	}


#pragma endregion


//////////////////// WIN / LOOSE BEHAVIOUR ////////////////////
#pragma region Win/Loose Behvaiour

void AMainCharacter::WinGame()
{
	if (AnimationHandler && WinMontage)
	{
		AnimationHandler->PlayAnimation(this, WinMontage);
		bCanMove = false;
	}

	if (MainCharacterController)
	{
		MainCharacterController->ShowWinScreen(true);
	}	
}

void AMainCharacter::LooseGame()
{
	if (AnimationHandler && LooseMontage)
	{
		AnimationHandler->PlayAnimation(this, LooseMontage);
		bCanMove = false;
	}

	if (MainCharacterController)
	{
		MainCharacterController->ShowLooseScreen(true);
	}
}
#pragma endregion


#pragma region "Change Object Transparency"

void AMainCharacter::ChangeObjectTransparency()
{
	TArray<FHitResult> HitResults;
	FVector ForwardVector = FollowCamera->GetForwardVector();
	FVector StartTrace = FollowCamera->GetComponentLocation();
	FVector EndTrace = StartTrace + (ForwardVector * CameraBoom->TargetArmLength);
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if (GetWorld()->LineTraceMultiByChannel(HitResults, StartTrace, EndTrace, ECC_WorldStatic, *TraceParams))
	{
		//we check all the hit objects to see if one of them has staticmesh component and then store it 
		for (auto& Hit : HitResults)
		{
			AActor* CurrentHitActor = Hit.GetActor();

			if (CheckIfIsPlayer(CurrentHitActor))
			{
				return;
			}

			GetStaticMeshes(CurrentHitActor);			
		}

		ChangeMaterials();
	}
}

bool AMainCharacter::CheckIfIsPlayer(AActor* CurrentHitActor)
{
	AMainCharacter* Player = Cast<AMainCharacter>(CurrentHitActor);
	
	if (Player != nullptr)
	{
		//if we touch te player we don't need to do anything
		//we only set back all the static mesh materials if there is any in the array
		for (int i = 0; i < CurrentHitMeshes.Num(); i++)
		{
			UStaticMeshComponent* CurrentHitMesh = CurrentHitMeshes[i];
			if (CurrentHitMesh == nullptr)
			{
				break;
			}
					
			UMaterial* CurrentHitObjectMaterial = CurrentHitObjectsMaterial[i];
			if (CurrentHitObjectMaterial == nullptr)
			{
				break;
			}
			CurrentHitMesh->SetMaterial(0, CurrentHitObjectMaterial);
		}
		CurrentHitMeshes.Empty();
		CurrentHitObjectsMaterial.Empty();

		return true;
	}
	
	return false;
}

void AMainCharacter::GetStaticMeshes(AActor* CurrentHitActor)
{
	AStaticMeshActor* StaticMeshActor = Cast<AStaticMeshActor>(CurrentHitActor);
	if (StaticMeshActor == nullptr)
	{
		return;
	}

	UStaticMeshComponent* StaticMeshComponent = StaticMeshActor->GetStaticMeshComponent();
	if (StaticMeshComponent == nullptr)
	{
		return;
	}
	
	if (!CurrentHitMeshes.Contains(StaticMeshComponent))
	{
		CurrentHitMeshes.Add(StaticMeshComponent);
		CurrentHitObjectsMaterial.Add(StaticMeshComponent->GetMaterial(0)->GetMaterial());
	}
}

void AMainCharacter::ChangeMaterials()
{
	//change the material of all static mesh we found 
	for (auto StaticMeshHit : CurrentHitMeshes)
	{
		if (StaticMeshHit == nullptr && CameraCollideMaterial == nullptr)
		{
			return;
		}
		
		StaticMeshHit->SetMaterial(0, CameraCollideMaterial);	
	}
}

#pragma endregion 

/**
 * @brief Define a character and his specification for the player
 * @param CharacterIndex Index for character in character array
 */
void AMainCharacter::DefinePlayerCharacter(int CharacterIndex)
{
	CharacterID = CharacterIndex;
	GetMesh()->SetSkeletalMesh(PlayableCharacters[CharacterIndex]);

	switch (CharacterIndex)
	{
	case 0:
		CarrySpeedBonus = 1.1;
		break;
		
	case 1:
		SpeedBonus = 1.1;
		break;
		
	case 2:
		CrouchSpeedBonus = 1.05;
		break;
		
	default:
		break;
	}
}

void AMainCharacter::SetGamePause()
{
	APlayerController* ControllerRef =  UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AMainCharacterController* Player = Cast<AMainCharacterController>(ControllerRef);

	if(Player != nullptr)
	{
		Player->ShowPauseMenu(true);
	}
}

