// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_LevelPickClass.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UUI_LevelPickClass::NativeConstruct()
{
	Super::NativeConstruct();

	
	BtnDungeonLevel->OnClicked.AddUniqueDynamic(this, &UUI_LevelPickClass::PlayDungeonLevel);
	BtnForgeLevel->OnClicked.AddUniqueDynamic(this, &UUI_LevelPickClass::PlayForgeLevel);
	BtnBack->OnClicked.AddUniqueDynamic(this, &UUI_LevelPickClass::Back);
	
	BtnDungeonLevel->OnClicked.AddUniqueDynamic(this, &UUI_LevelPickClass::HoverButton);
	BtnForgeLevel->OnClicked.AddUniqueDynamic(this, &UUI_LevelPickClass::HoverButton);
	BtnBack->OnHovered.AddUniqueDynamic(this, &UUI_LevelPickClass::HoverButton);

	UE_LOG(LogTemp, Warning, TEXT("INIT"));
}

void UUI_LevelPickClass::PlayDungeonLevel()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::SetGamePaused(World, false);
		UGameplayStatics::OpenLevel(World, DungeonLevelName);
	}
}

void UUI_LevelPickClass::PlayForgeLevel()
{
	UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::SetGamePaused(World, false);
		UGameplayStatics::OpenLevel(World, ForgeLevelName);
	}
}

void UUI_LevelPickClass::Back()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UUI_LevelPickClass::HoverButton()
{
	
}




