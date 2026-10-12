// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PickUp.h"

void APickUp::InitializePickUp(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity)
{
	if (!ItemDataTabel || DesiredItemID.IsNone())
	{
		return;
	}

	const FItemData* ItemData = ItemDataTabel->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());
	if (!ItemData)
	{
		return;
	}

	UClass* ItemClass = BaseClass.Get();
	if (!ItemClass)
	{
		ItemClass = UItemBase::StaticClass();
	}
	ItemRefrence = NewObject<UItemBase>(this, ItemClass);
	if (!ItemRefrence)
	{
		return;
	}

	ItemRefrence->ID = ItemData->ID;
	ItemRefrence->Type = ItemData->Type;
	ItemRefrence->Quality = ItemData->Quality;
	ItemRefrence->NumeracData = ItemData->NumeracData;
	ItemRefrence->TextDate = ItemData->TextDate;
	ItemRefrence->Statistcis = ItemData->Statistcis;
	ItemRefrence->AssetData = ItemData->AssetData;
	ItemRefrence->SetQuantity(InQuantity > 0 ? InQuantity : 1);

	if (PickMesh)
	{
		PickMesh->SetStaticMesh(ItemData->AssetData.StaticMesh);
	}

	UpdateInteracbleData();
}

void APickUp::IntilizedDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	if (!IsValid(ItemToDrop))
	{
		return;
	}

	ItemRefrence = ItemToDrop;
	ItemRefrence->SetQuantity(InQuantity > 0 ? InQuantity : 1);

	if (PickMesh)
	{
		PickMesh->SetStaticMesh(ItemToDrop->AssetData.StaticMesh);
	}

	UpdateInteracbleData();
}

void APickUp::BeginFocus()
{
	if (PickMesh)
	{
		PickMesh->SetRenderCustomDepth(true);
	}	
}

void APickUp::EndFocus()
{
	if (PickMesh)
	{
		PickMesh->SetRenderCustomDepth(false);
	}	
}

void APickUp::Interact(AArun_Character* Player)
{
	if (IsValid(Player) && IsValid(ItemRefrence))
	{
		TakePickUp(Player);
	}
}

void APickUp::UpdateInteracbleData()
{
	if (!IsValid(ItemRefrence))
	{
		return;
	}

	InstanceInteractabledata.InteratableType = EInteractionType::PickUp;
	InstanceInteractabledata.Action = ItemRefrence->TextDate.InteractionText;
	InstanceInteractabledata.Name = ItemRefrence->TextDate.Name;
	InstanceInteractabledata.Quantity = ItemRefrence->Quantity;
	Interactable = InstanceInteractabledata;
}

void APickUp::TakePickUp(const AArun_Character* Taker)
{
	if (!IsValid(Taker) || !IsValid(ItemRefrence))
	{
		return;
	}

	// Inventory handling can be added here once the character has an inventory component.
}

#if WITH_EDITOR
void APickUp::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	const FName ChangedPropertyName = PropertyChangedEvent.Property
		? PropertyChangedEvent.Property->GetFName()
		: NAME_None;
	
	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickUp, DesiredItemID) ||
		ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickUp, ItemDataTabel))
	{
		if (ItemDataTabel && !DesiredItemID.IsNone())
		{
			if (const FItemData* ItemData = ItemDataTabel->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString()))
			{
				if (PickMesh)
				{
					PickMesh->SetStaticMesh(ItemData->AssetData.StaticMesh);
				}
			}
		}
	}
}
#endif

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	PickMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickUpMesh");
	PickMesh->SetSimulatePhysics(true);
	SetRootComponent(PickMesh);

}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
	InitializePickUp(UItemBase::StaticClass(),ItemQuantity);
	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
