// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "DungeonsThief/Food//Food.h"
#include "HeadMountedDisplayTypes.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"



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
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Allow the mesh to be seen by the camera
	GetMesh()->SetOnlyOwnerSee(false);
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(WornFood != nullptr)
	{
		WornFood->SetActorLocation(this->GetActorLocation());
	}	
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

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::InteractWithItem);
}


/**
* @brief Pick random mesh from an array to set the UStaticMeshComponent mesh
*/
void AMainCharacter::InteractWithItem()
{
	if(TempActor != nullptr)
	{
		AFood* TempFood = Cast<AFood>(TempActor);
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
		DropItem();
	}
}

/**
* @brief Event when player carry item
*/
void AMainCharacter::CarryItem()
{
	if(IsCarryFood == false)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Carry item."));
		IsCarryFood = true;
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * 0.5;

		if(TempActor != nullptr)
		{
			WornFood = TempActor;
			WornFood->SetActorLocation(this->GetActorLocation());			
		}
	}
}

/**
* @brief Event when player drop item (on floor or on spot)
*/
void AMainCharacter::DropItem()
{
	if(IsCarryFood == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Drop item."));
		GetCharacterMovement()->MaxWalkSpeed = BaseSpeed;
		WornFood = nullptr;
		TempActor = nullptr;
		IsCarryFood = false;
	}
}

/*
 * Move the character in the forward or backward direction
 */
void AMainCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

/*
 * Move the character in the right or left direction
 */
void AMainCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookupRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookupRate * GetWorld()->GetDeltaSeconds());
}

