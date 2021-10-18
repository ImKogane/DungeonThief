// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_MainClass.h"
#include "Components/ProgressBar.h"
#include "DungeonsThief/MyGameMode.h"
#include "DungeonsThief/MyGameState.h"


class AMyGameMode;

void UUI_MainClass::NativeConstruct()
{
	Super::NativeConstruct();

	AGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode();
	if (GameModeBase == nullptr)
	{
		return;
	}

	AMyGameMode* MyGameMode = Cast<AMyGameMode>(GameModeBase);
	if (MyGameMode == nullptr)
	{
		return;
	}

	MyGameState = MyGameMode->GetGameState<AMyGameState>();
}

void UUI_MainClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if(MyGameState)
	{
		FoodBar->SetPercent(MyGameState->GetProgressionPercent());	//Set progress bar value
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Crouch."));
	}
	
}
