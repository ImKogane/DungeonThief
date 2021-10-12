// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/Player/MainCharacterController.h"
#include "Blueprint/UserWidget.h"


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

	
}
