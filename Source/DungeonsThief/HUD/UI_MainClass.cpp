// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_MainClass.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "DungeonsThief/GameSettings/MyGameMode.h"
#include "DungeonsThief/GameSettings/MyGameState.h"
#include "DungeonsThief/GameSettings/MyGameInstance.h"


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
	
	GameInstance = Cast<UMyGameInstance>(GetGameInstance());
	
	MyGameState = MyGameMode->GetGameState<AMyGameState>();

	if(GameInstance == nullptr)
		return;
	
	if(GameInstance->GetGameplayMode() == EGameplayMode::EGM_ScoreMode)
	{
		ScorePoint->SetVisibility(ESlateVisibility::Visible);
		FoodBar->SetPercent(1.0f);
	}
	else
	{
		ScorePoint->SetVisibility(ESlateVisibility::Hidden);
		FoodBar->SetPercent(0.0f);
	}

	MyGameMode->OnGainPoints.AddDynamic(this, &UUI_MainClass::UpdateProgression);
}

void UUI_MainClass::UpdateProgression()
{
	if(GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance null"));
		return;
	}
	
	if(GameInstance->GetGameplayMode() == EGameplayMode::EGM_NormalMode)
	{
		if(MyGameState)
		{
			FoodBar->SetPercent(MyGameState->GetProgressionPercent());	//Set progress bar value
		}
	}
	else
	{
		if(MyGameState)
		{
			ScorePoint->SetText(FText::AsNumber(MyGameState->GetPlayerPoints()));
		}
	}
}
