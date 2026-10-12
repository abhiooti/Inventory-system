// Fill out your copyright notice in the Description page of Project Settings.


#include "UserInterface/Interaction/Interaction_Widget.h"

#include "Components/ProgressBar.h"

void UInteraction_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	InteractionProgressbar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UInteraction_Widget::NativeConstruct()
{
	Super::NativeConstruct();
	
	KeyPressText->SetText(FText::FromString("Press"));
	currentinteractionduration = 0.0f;
}

void UInteraction_Widget::UpdateWidget(const FInteractabledata* Interactabledata)
{
	switch (Interactabledata->InteratableType)
	{
	case EInteractionType::PickUp:
		KeyPressText->SetText(FText::FromString("Press"));
		InteractionProgressbar->SetVisibility(ESlateVisibility::Collapsed);

		if (Interactabledata->Quantity < 2)
		{
			Quantity->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			Quantity->SetText(FText::Format(NSLOCTEXT("InteractionWidget ","Quantity","x{0}"),Interactabledata->Quantity));
			Quantity->SetVisibility(ESlateVisibility::Visible);	
		}
		break;
		
	case EInteractionType::NonPlayerCharcater:
		break;
		
	case EInteractionType::Device:
		break;
		
	case EInteractionType::Toggle:
		break;
		
	case EInteractionType::container:
		break;
	}
	actionText->SetText(Interactabledata->Action);
	NameBlock->SetText(Interactabledata->Name);
}

float UInteraction_Widget::UpdateInteractionProgress()
{
	return 0.0f;
}

