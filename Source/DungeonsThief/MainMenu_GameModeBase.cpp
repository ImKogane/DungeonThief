// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/GameSettings/MainMenu_GameModeBase.h"

#include "LevelSequencePlayer.h"
#include "HUD/MainMenuController.h"
#include "Kismet/GameplayStatics.h"

void AMainMenu_GameModeBase::BeginPlay()
{	
}

void AMainMenu_GameModeBase::ShowPickLevelWidget()
{
	AMainMenuController* MenuController = Cast<AMainMenuController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if(MenuController != nullptr)
	{
		MenuController->ShowPickLevelMenu();
	}
}



