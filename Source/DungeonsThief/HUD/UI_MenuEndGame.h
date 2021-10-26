// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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
	
	UFUNCTION()
	void ReturnToMenu();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Restart Game")
    class UButton* BtnPlayAgain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Restart Game")
	class UButton* BtnMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Restart Game")
	class UTextBlock* EndScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Restart Game")
	class UTextBlock* EndBestScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "Restart Game")
	bool bLoseUI;

	
	class UMyGameInstance* MyGameInstance;
	
    UPROPERTY(EditAnywhere, Category = "Restart Game")
    FName MainLevelName = FName("MainLevel");
	
	UPROPERTY(EditAnywhere, Category = "Restart Game")
	FName MainMenuLevelName = FName("MainMenuLevel");

public:
	void SetTextScore(int Score);
	
};
