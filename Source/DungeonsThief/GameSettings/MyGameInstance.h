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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int BestScore = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PlayerXP = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int PlayerXPLevel = 0;

public:
	FORCEINLINE void SetGameplayMode(EGameplayMode GameplayModeValue) {GameplayMode = GameplayModeValue; }
	FORCEINLINE EGameplayMode GetGameplayMode() { return GameplayMode; }

	//Best score system variable
	FORCEINLINE int GetBestScore() { return BestScore; }
	FORCEINLINE void SetBestScore(int NewBestScore);
	
	//Player XP system variable
	FORCEINLINE int GetPlayerXP() { return PlayerXP; }
	FORCEINLINE void AddPlayerXP(int AmountOfXP);

	//Plauer XP Level system variable
	FORCEINLINE int GetPlayerXPLevel() { return PlayerXPLevel; }

	//Save system
	void SaveGame();
	void LoadGame();
	
};
