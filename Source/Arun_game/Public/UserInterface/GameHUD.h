// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Player/Arun_Character.h"
#include "GameHUD.generated.h"

struct FInteractionData;
class UInteraction_Widget;
class UMainMenu;

/**
 * 
 */
UCLASS()
class ARUN_GAME_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly,Category="Widgits")
	TSubclassOf<UMainMenu> MainMenuClass;
	
	UPROPERTY(EditDefaultsOnly,Category="Widgits")
	TSubclassOf<UInteraction_Widget> InteractionClass;
	
	bool BismenuVisble;
public:
	AGameHUD();
	//FUNCTIONS
	void Displaymenu();
	void Hidemenu();
	
	void showInteractionWidget();
	void HideInteractionWidget();

	void UpdateInteractionWidget(const FInteractabledata* InteractableData);
	
protected:
	UPROPERTY()
	UMainMenu* MainMenuWidget;
	
	UPROPERTY()
	UInteraction_Widget* InteractionWidget;
	
	virtual void BeginPlay() override;
	
};
