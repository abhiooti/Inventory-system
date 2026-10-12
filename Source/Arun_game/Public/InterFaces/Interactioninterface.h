// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactioninterface.generated.h"

class AArun_Character;
UENUM()
enum class EInteractionType : uint8
{
	PickUp UMETA(DisplayName = "PickUp"),
	NonPlayerCharcater UMETA(DisplayName = "NonPlayerCharcater"),
	Device UMETA(DisplayName = "Device"),
	Toggle UMETA(DisplayName = "Toggle"),
	container UMETA(DisplayName = "container"),
};
USTRUCT()
struct FInteractabledata
{
	GENERATED_USTRUCT_BODY()
	
	FInteractabledata() : 
	InteratableType(EInteractionType::PickUp),
	Name(FText::GetEmpty()),
	Action(FText::GetEmpty()),
	Quantity(0),
	InterActionDuration(0.0f)
	{
		
	}
	
	UPROPERTY(EditInstanceOnly)
	EInteractionType InteratableType;
	
	UPROPERTY(EditInstanceOnly)
	FText Name;
	//only for pickups
	UPROPERTY(EditInstanceOnly)
	int8 Quantity;
	
	UPROPERTY(EditInstanceOnly)
	FText Action;
	//used for things like values , doors , etc that requires an interaction timer
	UPROPERTY(EditInstanceOnly)	
	float InterActionDuration;
};
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractioninterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARUN_GAME_API IInteractioninterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void BeginFocus();
	virtual void EndFocus();
	virtual void BeginInteraction();
	virtual void EndInteraction();
	virtual void Interact(AArun_Character* player);
	
	FInteractabledata Interactable;
	
};
