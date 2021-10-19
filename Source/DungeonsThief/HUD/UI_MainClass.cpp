// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_MainClass.h"
#include "Components/ProgressBar.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/GameSettings/MyGameState.h"


class AMyGameMode;

void UUI_MainClass::NativeConstruct()
{
	Super::NativeConstruct();

	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase == nullptr)
	{
		return;
	}

	MyGameMode = Cast<AMyGameMode>(GameModeBase);
	if (MyGameMode == nullptr)
	{
		return;
	}

	MyGameState = MyGameMode->GetGameState<AMyGameState>();

	MyGameMode->OnGainPoints.AddDynamic(this, &UUI_MainClass::UpdateProgression);
}

void UUI_MainClass::UpdateProgression()
{
	if(MyGameState)
	{
		FoodBar->SetPercent(MyGameState->GetProgressionPercent());	//Set progress bar value
	}
}
