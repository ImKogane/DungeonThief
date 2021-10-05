// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacterAnimInstance.h"
#include "MainCharacter.h"


void UMainCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
	
	if (Pawn)
	{
		MainCharacter = Cast<AMainCharacter>(Pawn);
	}
	
}

void UMainCharacterAnimInstance::UpdateAnimationProperties()
{
	//UE_LOG(LogTemp, Warning, TEXT("PLAYER : %f"), MovementSpeed);

	if (MainCharacter)
	{
		MovementSpeed = GetCharacterMovementSpeed();
	}
}

void UMainCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateAnimationProperties();
}

float UMainCharacterAnimInstance::GetCharacterMovementSpeed()
{
	if (MainCharacter)
	{
		FVector Speed = MainCharacter->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		return LateralSpeed.Size();
	}

	return 0;
}
