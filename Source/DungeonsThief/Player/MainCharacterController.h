// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API AMainCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacterController();
	
protected:

	virtual void BeginPlay() override;
	
	/** Reference to the UMG asset in the editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> WMain;

	/** Variable to hold the wodget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* MainWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> WWinScreen;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* WinScreenWidget;

	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> WLooseScreen;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* LooseScreenWidget;
	
	UPROPERTY(EditAnywhere, Category = "Widget")
    TSubclassOf<UUserWidget> WPauseMenu;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
    UUserWidget* PauseMenuWidget;

	/** Reference to the character pick UMG asset in the editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> WCharacterPick;

	/** Variable to hold the Character pick widget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* CharacterPickWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller infos")
	bool CanPause = false;
	

public :

	void ShowWinScreen(bool Visibility);
	void ShowLooseScreen(bool Visibility);
	void ShowPauseMenu(bool Visibility);
	void ShowMainHUD(bool Visibility);
	void ShowCharacterHUD(bool Visibility);

	void SetCanPause(bool state);
	

};
