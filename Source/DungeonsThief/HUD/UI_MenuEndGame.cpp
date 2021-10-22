// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MenuEndGame.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UUI_MenuEndGame::NativeConstruct()
{
	Super::NativeConstruct();
	
	BtnPlayAgain->OnClicked.AddUniqueDynamic(this, &UUI_MenuEndGame::RestartGame);
	BtnMenu->OnClicked.AddUniqueDynamic(this, &UUI_MenuEndGame::ReturnToMenu);

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

