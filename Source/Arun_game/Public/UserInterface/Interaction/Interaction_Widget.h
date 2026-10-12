// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Player/Arun_Character.h"
#include "Interaction_Widget.generated.h"

struct FInteractableData;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class ARUN_GAME_API UInteraction_Widget : public UUserWidget
{
	GENERATED_BODY()
	
	public:
	
	UPROPERTY(EditAnywhere,Category="Interaction || PlayerReference")
	AArun_Character* CharacterRef;
	
	void UpdateWidget(const FInteractabledata* Interactabledata);
	
protected:
	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category="Interaction || PlayerReference")
	UTextBlock* NameBlock;
	
	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category="Interaction || PlayerReference")
	UTextBlock* actionText;
	
	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category="Interaction || PlayerReference")
	UTextBlock* Quantity;
	
	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category="Interaction || PlayerReference")
	UTextBlock* KeyPressText;
	
	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category="Interaction || PlayerReference")
	UProgressBar* InteractionProgressbar;
	
	UPROPERTY(VisibleAnywhere,meta=(BindWidget),Category="Interaction || PlayerReference")
	float currentinteractionduration;
	
	UFUNCTION()
	float UpdateInteractionProgress();
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
};
