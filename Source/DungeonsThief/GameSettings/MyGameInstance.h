// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyGameState.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EGameplayMode GameplayMode = EGameplayMode::EGM_NormalMode;

public:
	FORCEINLINE void SetGameplayMode(EGameplayMode GameplayModeValue) {GameplayMode = GameplayModeValue; }
	FORCEINLINE EGameplayMode GetGameplayMode() { return GameplayMode; }
	
};
