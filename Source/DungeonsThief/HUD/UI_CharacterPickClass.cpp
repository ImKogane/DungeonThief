// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonsThief/HUD/UI_CharacterPickClass.h"

#include "Components/Button.h"
#include "DungeonsThief/Player/MainCharacter.h"
#include "DungeonsThief/Player/MainCharacterController.h"
#include "Kismet/GameplayStatics.h"

void UUI_CharacterPickClass::NativeConstruct()
{
	Super::NativeConstruct();
	
	BtnCharacter1->OnClicked.AddUniqueDynamic(this, &UUI_CharacterPickClass::ChooseCharacter1);
	BtnCharacter2->OnClicked.AddUniqueDynamic(this, &UUI_CharacterPickClass::ChooseCharacter2);
	BtnCharacter3->OnClicked.AddUniqueDynamic(this, &UUI_CharacterPickClass::ChooseCharacter3);
	
	BtnCharacter1->OnClicked.AddUniqueDynamic(this, &UUI_CharacterPickClass::HoverButton);
	BtnCharacter2->OnClicked.AddUniqueDynamic(this, &UUI_CharacterPickClass::HoverButton);
	BtnCharacter3->OnHovered.AddUniqueDynamic(this, &UUI_CharacterPickClass::HoverButton);
}

void UUI_CharacterPickClass::ChooseCharacter1()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("1"));
	AMainCharacter* PlayerRef = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	if(PlayerRef != nullptr)
	{
		PlayerRef->DefinePlayerCharacter(0);
		HideHUD();
	}
}

void UUI_CharacterPickClass::ChooseCharacter2()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("2"));
	AMainCharacter* PlayerRef = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	if(PlayerRef != nullptr)
	{
		PlayerRef->DefinePlayerCharacter(1);
		HideHUD();
	}
}

void UUI_CharacterPickClass::ChooseCharacter3()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("3"));
	AMainCharacter* PlayerRef = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	if(PlayerRef != nullptr)
	{
		PlayerRef->DefinePlayerCharacter(2);
		HideHUD();
	}
}

void UUI_CharacterPickClass::HoverButton()
{
	
}

void UUI_CharacterPickClass::HideHUD()
{
	AMainCharacterController* ControllerRef = Cast<AMainCharacterController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if(ControllerRef != nullptr)
	{
		this->SetVisibility(ESlateVisibility::Hidden);
		UGameplayStatics::GetPlayerController(GetWorld(),0)->bShowMouseCursor = false;
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		ControllerRef->SetCanPause(true);
		
	}
}





