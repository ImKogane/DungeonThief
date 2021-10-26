// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MenuEndGame.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DungeonsThief/GameSettings/MySaveGame.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"
#include "DungeonsThief/GameSettings/MySaveGame.h"
#include "Kismet/GameplayStatics.h"


void UUI_MenuEndGame::NativeConstruct()
{
	Super::NativeConstruct();
	
	BtnPlayAgain->OnClicked.AddUniqueDynamic(this, &UUI_MenuEndGame::RestartGame);
	BtnMenu->OnClicked.AddUniqueDynamic(this, &UUI_MenuEndGame::ReturnToMenu);
	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if(bLoseUI && MyGameInstance->GetGameplayMode() == EGameplayMode::EGM_ScoreMode)
	{
		EndScore->SetVisibility(ESlateVisibility::Visible);
		EndBestScore->SetVisibility(ESlateVisibility::Visible);
		
	}
	else
	{
		EndScore->SetVisibility(ESlateVisibility::Hidden);
		EndBestScore->SetVisibility(ESlateVisibility::Hidden);
	}
	
	MainLevelName = FName(GetWorld()->GetName());
}

void UUI_MenuEndGame::RestartGame()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, MainLevelName);
	}
}

void UUI_MenuEndGame::ReturnToMenu()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, MainMenuLevelName);
	}
}

void UUI_MenuEndGame::SetTextScore(int Score)
{
	int SavedScore = MyGameInstance->GetBestScore();
	
	EndScore->SetText(FText::Format(FText::FromString("Your score : {0}"), Score));

	if(Score > SavedScore)
	{
		EndBestScore->SetText(FText::Format(FText::FromString("Best score : {0}"), Score));

		//Call score system of the game instance
		MyGameInstance->SetBestScore(Score);
	}
	else
	{
		EndBestScore->SetText(FText::Format(FText::FromString("Best score : {0}"), SavedScore));
	}
	
}



