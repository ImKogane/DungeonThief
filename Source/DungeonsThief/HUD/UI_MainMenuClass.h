// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_MainMenuClass.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API UUI_MainMenuClass : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnPlay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnPlayScore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnExit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget), Category = "UIElements")
	class UButton* BtnTutorial;

	UFUNCTION()
	void PlayNormalGame();

	UFUNCTION()
	void PlayScoreGame();

	UFUNCTION()
	void PlayGame(enum EGameplayMode GameplayMode);
	
	UFUNCTION()
	void OpenSettings();
	
	UFUNCTION()
	void OpenTutorial();

	UFUNCTION()
	void ExitGame();

	UPROPERTY(VisibleAnywhere, Category = "UI infos")
	class UMyGameInstance* MyGameInstance;

	UPROPERTY(EditAnywhere, Category = "UI infos")
	FName LevelToLoadName = FName("MainLevel");
};
