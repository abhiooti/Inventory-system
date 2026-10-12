// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class AArun_Character;
/**
 * 
 */
UCLASS()
class ARUN_GAME_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()



public:
	UPROPERTY()
	AArun_Character* PlayerCharacter;
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;
	
};
