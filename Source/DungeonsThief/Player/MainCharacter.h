// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonsThief/Food/CarryingCharacter.h"
#include "DungeonsThief/Food/FoodSpot.h"

#include "MainCharacter.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AMainCharacter : public ACarryingCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	
protected: 
	// For variable declaration
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* CAMERA SECTION */
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float BaseLookupRate;

	UPROPERTY(EditAnywhere, Category = "CameraZoom")
	float MaxZoom;
	
	UPROPERTY(EditAnywhere, Category = "CameraZoom")
	float MinZoom;

	class AAnimationsHandler* AnimationHandler;

	UPROPERTY(EditAnywhere, Category = "Animations")
	class UAnimMontage* WinMontage;
	
	UPROPERTY(EditAnywhere, Category = "Animations")
	class UAnimMontage* LooseMontage;

	UPROPERTY(EditAnywhere, Category = "Animations")
	bool IsCrouch = false;

	UPROPERTY(VisibleAnywhere, Category = "PlayeModel")
	int CharacterID = 0;
	
	UPROPERTY(EditAnywhere, Category = "PlayeModel")
	TArray<USkeletalMesh*> PlayableCharacters;
	
	bool bCanMove;
	
protected:
	//For function declaration

	/* Called for crouch player */
	void CrouchPlayer();
	
	/* Called for remove crouch state of player */
	void UnCrouchPlayer();
	
	/* Called for forward and backward movement */
	void MoveForward(float Value);

	/* Called for right and left movement */
	void MoveRight(float Value);

	/* Called via input to turn at a giver rate*/
	void TurnAtRate(float Rate);

	/* Called via input to look up and down at a given rate*/
	void LookupRate(float Rate);

	/* Called for scrolling in or out the camera view*/
	void ScrollInOut(float Value);

public:
	FORCEINLINE void SetCanMove(bool value) { bCanMove = value; }
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void WinGame();

	void LooseGame();

	void TestWin();

	FORCEINLINE bool GetIsCrouching() { return IsCrouch; }
	
	FORCEINLINE int GetCharacterID() { return CharacterID; } 
	


	
};


