// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class DUNGEONSTHIEF_API AMainCharacter : public ACharacter
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
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float BaseSpeed;
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	float Speed;

	UPROPERTY(VisibleAnywhere, Category = "Food")
	bool IsCarryFood;

	UPROPERTY(VisibleAnywhere, Category = "Other")
	class AActor* TempActor;
	
	UPROPERTY(VisibleAnywhere, Category = "Food")
	AActor* WornFood;

	
	
	
	UFUNCTION()
	void InteractWithItem();

	UFUNCTION()
	void CarryItem();

	
	
protected:
	//For function declaration

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

	UPROPERTY(EditAnywhere, Category = "CameraZoom")
	float MaxZoom;
	UPROPERTY(EditAnywhere, Category = "CameraZoom")
	float MinZoom;
	

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:

	void SetPlayerActor(AActor* NewActor);
	void SetSpeed(float NewSpeed);

	UFUNCTION()
		void DropItem();
	
	bool GetIsCarryFood();
	AActor* GetWornFood();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
