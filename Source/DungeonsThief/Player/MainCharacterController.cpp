// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Player/MainCharacterController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


AMainCharacterController::AMainCharacterController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMainCharacterController::BeginPlay()
{
	Super::BeginPlay();

	if (WMain)
	{
		MainWidget = CreateWidget<UUserWidget>(this, WMain);
		MainWidget->AddToViewport();
        MainWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (WCharacterPick)
	{
		CharacterPickWidget = CreateWidget<UUserWidget>(this, WCharacterPick);
		CharacterPickWidget->AddToViewport();
		CharacterPickWidget->SetVisibility(ESlateVisibility::Visible);
	}

	if (WWinScreen)
	{
		WinScreenWidget = CreateWidget<UUserWidget>(this, WWinScreen);
		if (WinScreenWidget)
		{
			WinScreenWidget->AddToViewport();
			WinScreenWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (WLooseScreen)
	{
		LooseScreenWidget = CreateWidget<UUserWidget>(this, WLooseScreen);
		if (LooseScreenWidget)
		{
			LooseScreenWidget->AddToViewport();
			LooseScreenWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
	if (WPauseMenu)
	{
		PauseMenuWidget = CreateWidget<UUserWidget>(this, WPauseMenu);
		if (PauseMenuWidget)
		{
			PauseMenuWidget->AddToViewport();
			PauseMenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
	bShowMouseCursor = true;
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AMainCharacterController::ShowWinScreen(bool Visibility)
{
	WinScreenWidget->SetVisibility(Visibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	bShowMouseCursor = true;
}

void AMainCharacterController::ShowLooseScreen(bool Visibility)
{
	LooseScreenWidget->SetVisibility(Visibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	bShowMouseCursor = true;
}

void AMainCharacterController::ShowPauseMenu(bool Visibility)
{

	if(CanPause)
	{
		PauseMenuWidget->SetVisibility(Visibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		bShowMouseCursor = true;
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
	
}

void AMainCharacterController::ShowMainHUD(bool Visibility)
{
	MainWidget->SetVisibility(Visibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	if(Visibility == true)
	{
		SetCanPause(true);
	}
}

void AMainCharacterController::ShowCharacterHUD(bool Visibility)
{
	CharacterPickWidget->SetVisibility(Visibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

	if(Visibility == false)
	{
		CanPause = true;
	}
	
}

void AMainCharacterController::SetCanPause(bool state)
{
	CanPause = state;
}
