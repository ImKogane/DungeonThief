// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuController.generated.h"

UENUM(BlueprintType)
enum class EWidgetMainMenuScreen : uint8
{
	EWMMS_PickLevel UMETA(DisplayName = "PickLevelScreen"),
	EWMMS_Settings UMETA(DisplayName = "SettingsScreen"),
	EWMMS_Tutorial UMETA(DisplayName = "TutorialScreen"),
	EWMMS_MainMenu UMETA(DisplayName = "MainMenucreen"),
	EWMMS_SkinSelector UMETA(DisplayName = "SkinSelectorScreen")
};

/**
 * 
 */
UCLASS()
class DUNGEONSTHIEF_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	/** Reference to the menu UMG asset in the editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> MainMenuWidget;

	/** Variable to hold the main menu widget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* MainMenu;


	/** Reference to the pick level menu UMG asset in the editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> PickLevelWidget;

	/** Variable to hold the level menu widget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* PickLevelMenu;

	/** Reference to the settings menu UMG asset in the editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> SettingsWidget;

	/** Variable to hold the level menu widget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* SettingsMenu;

	/** Reference to the tutorial widget UMG asset in the editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> TutorialWidget;

	/** Variable to hold the level menu widget after creating it */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* TutorialMenu;

	/** Reference to the pick level menu UMG asset in the editor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<class UUserWidget> SkinSelectionWidget;

	/** Variable to hold the skin selection menu **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* SkinSelectionMenu;

public:
	UFUNCTION()
	void ShowScreen(bool Visibility, EWidgetMainMenuScreen GameScreen);
};
