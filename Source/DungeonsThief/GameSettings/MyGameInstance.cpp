// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/GameSettings/MyGameInstance.h"

#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::SetBestScore(int NewBestScore)
{
	BestScore = NewBestScore;
	SaveGame();
	
}

void UMyGameInstance::AddPlayerXP(int AmountOfXP)
{
	PlayerXP += AmountOfXP;
	if(PlayerXP>=100)
	{
		PlayerXPLevel++;
		PlayerXP -= 100;
	}

	SaveGame();
}

void UMyGameInstance::SaveGame()
{
	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

	SaveGameInstance->BestPlayerScore = BestScore;
	SaveGameInstance->PlayerXP = PlayerXPLevel;
	SaveGameInstance->PlayerXPLevel = PlayerXPLevel;
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("Save"), 0);
}


void UMyGameInstance::LoadGame()
{
	if(!UGameplayStatics::DoesSaveGameExist("Save",0))
	{
		SaveGame();
	}

	UMySaveGame* SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));
	SaveGameInstance = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot("Save",0));

	//Define the best score variable with saved value
	BestScore = SaveGameInstance->BestPlayerScore;
	//Define the player XP variable with saved value
	PlayerXP = SaveGameInstance->PlayerXP;
	//Define the player XP Level variable with saved value
	PlayerXPLevel = SaveGameInstance->PlayerXPLevel;
	
}
