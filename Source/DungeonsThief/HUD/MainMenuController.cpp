// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/MainMenuController.h"

#include "Blueprint/UserWidget.h"

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidget)
	{
		MainMenu = CreateWidget<UUserWidget>(this, MainMenuWidget);
		MainMenu->AddToViewport();
		MainMenu->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
	}
	
}
