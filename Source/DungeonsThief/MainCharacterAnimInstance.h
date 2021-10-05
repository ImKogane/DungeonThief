// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UMainCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public :

    virtual void NativeInitializeAnimation() override;
    
    UFUNCTION(BlueprintCallable, Category = "AnimationProperties")
	void UpdateAnimationProperties();

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimationProperties")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class AMainCharacter* MainCharacter;
};
