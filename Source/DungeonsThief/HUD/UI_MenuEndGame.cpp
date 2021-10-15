// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_MenuEndGame.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UUI_MenuEndGame::NativeConstruct()
{
	Super::NativeConstruct();
	
	LevelToLoadName = FName("MainLevel");
	BtnPlayAgain->OnClicked.AddUniqueDynamic(this, &UUI_MenuEndGame::RestartGame);
	UE_LOG(LogTemp, Warning, TEXT("INIT"));
}

void UUI_MenuEndGame::RestartGame()
{
	UWorld* World = GetWorld();
	UE_LOG(LogTemp, Warning, TEXT("RESTART"));

	if (World)
	{
		UE_LOG(LogTemp, Warning, TEXT("RESTART"));
		UGameplayStatics::OpenLevel(World, LevelToLoadName);
	}
}
