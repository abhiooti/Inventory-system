// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/IneventoryComponent.h"

// Sets default values for this component's properties
UIneventoryComponent::UIneventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UItemBase* UIneventoryComponent::findMatchingItem(UItemBase* ItemIn) const
{
	if (ItemIn)
	{
		if (InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}
	return nullptr;
}

UItemBase* UIneventoryComponent::findNextItemByID(UItemBase* ItemIn) const
{
	if (ItemIn)
	{
		if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}
}

UItemBase* UIneventoryComponent::findPartialStack(UItemBase* ItemIn) const
{
	return ItemIn;
}

FItemAddResult UIneventoryComponent::HandleAddItem(UItemBase* InputItem)
{
}

void UIneventoryComponent::RemoveSingleInstanceOfItem(UItemBase* ItemIn)
{
}

int32 UIneventoryComponent::RemoveAmountItem(UItemBase* ItemIn, int32 DesiredAmountToRemove)
{
}

void UIneventoryComponent::SplitExisistingStack(UItemBase* ItemIn, int32 AmountToSplit)
{
}

FItemAddResult UIneventoryComponent::HandleNonStackbleItems(UItemBase*, int32 RequestedAddAmount)
{
}

int32 UIneventoryComponent::HandleStackableItems(UItemBase*, int32 RequestedAddAmount)
{
}

int32 UIneventoryComponent::CalucalteWeghitAddAmount(UItemBase*, int32 RequestedAddAmount)
{
}

int32 UIneventoryComponent::CalculateNumberForFullStack(UItemBase* ExisitingItem, int32 IntitalRequestedAddAmount)
{
}

void UIneventoryComponent::AddNewItem(UItemBase* Item, const int32 AmountAdd)
{
}


// Called when the game starts
void UIneventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}




