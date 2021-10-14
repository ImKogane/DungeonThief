// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_MenuEndGame.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UUI_MenuEndGame : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	virtual void NativeConstruct() override;

	UFUNCTION()
    void RestartGame();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Restart Game")
    class UButton* BtnPlayAgain;
    
    UPROPERTY(EditAnywhere, Category = "Restart Game")
    FName LevelToLoadName;
};
