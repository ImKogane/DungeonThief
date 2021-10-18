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

	if (HUDOverlayAsset)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
		HUDOverlay->AddToViewport();
        HUDOverlay->SetVisibility(ESlateVisibility::Visible);
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
	PauseMenuWidget->SetVisibility(Visibility ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	bShowMouseCursor = true;
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
