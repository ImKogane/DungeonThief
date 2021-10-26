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
	UE_LOG(LogTemp, Warning, TEXT("INIT"));
}

void UUI_MenuEndGame::RestartGame()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("RESTART"));
		UGameplayStatics::OpenLevel(World, MainLevelName);
	}
}

void UUI_MenuEndGame::ReturnToMenu()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("MENU"));
		UGameplayStatics::OpenLevel(World, MainMenuLevelName);
	}
}

void UUI_MenuEndGame::SetTextScore(int Score)
{
	int SavedScore = 0;
	SavedScore = LoadScore();
	
	EndScore->SetText(FText::Format(FText::FromString("Your score : {0}"), Score));

	if(Score > SavedScore)
	{
		UE_LOG(LogTemp, Warning, TEXT("Best score") );
		EndBestScore->SetText(FText::Format(FText::FromString("Best score : {0}"), Score));
		SaveData(Score);
	}
	else
	{
		EndBestScore->SetText(FText::Format(FText::FromString("Best score : {0}"), SavedScore));
	}
	
}

int UUI_MenuEndGame::LoadScore()
{
	int score = 0;
	
	if(!UGameplayStatics::DoesSaveGameExist("Save",0))
	{
		SaveData(0);
	}

	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("Save",0));
	score = SaveGameInstance->BestPlayerScore;
	
	return score;
}

void UUI_MenuEndGame::SaveData(int score)
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	
	SaveGameInstance->BestPlayerScore = score;
	

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Save"), 0);

	
	
}


