// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_MainMenuClass.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UUI_MainMenuClass::NativeConstruct()
{
	Super::NativeConstruct();

	
	BtnPlay->OnClicked.AddUniqueDynamic(this, &UUI_MainMenuClass::PlayNormalGame);
	BtnPlayScore->OnClicked.AddUniqueDynamic(this, &UUI_MainMenuClass::PlayScoreGame);
	BtnSettings->OnClicked.AddUniqueDynamic(this, &UUI_MainMenuClass::OpenSettings);
	BtnExit->OnClicked.AddUniqueDynamic(this, &UUI_MainMenuClass::ExitGame);

	UE_LOG(LogTemp, Warning, TEXT("INIT"));
}

void UUI_MainMenuClass::PlayNormalGame()
{
	UWorld* World = GetWorld();
	UE_LOG(LogTemp, Warning, TEXT("START GAME"));

	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("START GAME"));
		UGameplayStatics::SetGamePaused(World, false);
		UGameplayStatics::OpenLevel(World, LevelToLoadName);
	}
}

void UUI_MainMenuClass::PlayScoreGame()
{
	UE_LOG(LogTemp, Warning, TEXT("START SCORE GAME"));
}


void UUI_MainMenuClass::OpenSettings()
{
	UE_LOG(LogTemp, Warning, TEXT("OPEN SETTINGS"));
}

void UUI_MainMenuClass::ExitGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	UE_LOG(LogTemp, Warning, TEXT("EXIT GAME"));
}


