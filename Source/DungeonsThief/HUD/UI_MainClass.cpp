// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_MainClass.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ProgressBar.h"
#include "DungeonsThief/GameManager.h"


void UUI_MainClass::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//Try to fond the game object actor in the world
	TArray<AActor*> LeGameManager;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameManager::StaticClass(), LeGameManager);

	AGameManager* Manager = Cast<AGameManager>(LeGameManager[0]);
	if(Manager != nullptr)
	{
		float percent = (Manager->GetPoints());
		FoodBar->SetPercent(percent/5);	//Set progress bar value
	}
}
