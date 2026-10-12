// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/GameHUD.h"
#include "UserInterface/MainMenu.h"
#include "UserInterface/Interaction/Interaction_Widget.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();
	if (MainMenuClass)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (InteractionClass)
	{
		InteractionWidget = CreateWidget<UInteraction_Widget>(GetWorld(), InteractionClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}
AGameHUD::AGameHUD()
{
}

void AGameHUD::Displaymenu()
{
	if (MainMenuWidget)
	{
		BismenuVisble = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AGameHUD::Hidemenu()
{
	if (MainMenuWidget)
	{
		BismenuVisble = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AGameHUD::showInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AGameHUD::HideInteractionWidget()
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AGameHUD::UpdateInteractionWidget(const FInteractabledata* InteractableData)
{
	if (!InteractionWidget || !InteractableData)
	{
		return;
	}

	InteractionWidget->UpdateWidget(InteractableData);
	InteractionWidget->SetVisibility(ESlateVisibility::Visible);
}
