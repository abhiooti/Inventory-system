// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterFaces/Interactioninterface.h"
#include "Items/ItemBase.h"
#include "PickUp.generated.h"

UCLASS()
class ARUN_GAME_API APickUp : public AActor , public IInteractioninterface
{
	GENERATED_BODY()
	
public:	
	
	void InitializePickUp(const TSubclassOf<UItemBase> BaseClass,const int32 InQuantity);
	
	void IntilizedDrop(UItemBase* ItemToDrop,const int32 InQuantity);
	
	FORCEINLINE UItemBase* GetItemData(){return ItemRefrence;}
	// Sets default values for this actor's properties
	APickUp();
	
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void Interact(AArun_Character* player) override;
	void UpdateInteracbleData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,Category="PickUp")	
	UStaticMeshComponent* PickMesh;
	
	UPROPERTY(EditInstanceOnly,Category="PickUp")	
	UDataTable* ItemDataTabel;
	
	UPROPERTY(EditInstanceOnly,Category="PickUp")	
	FName DesiredItemID;
	
	UPROPERTY(VisibleAnywhere,Category="PickUp")	
	UItemBase* ItemRefrence;
	
	UPROPERTY(EditInstanceOnly,Category="PickUp")	
	int32 ItemQuantity;
	
	UPROPERTY(VisibleInstanceOnly,Category="PickUp")	
	FInteractabledata InstanceInteractabledata;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
	void TakePickUp(const AArun_Character* Taker);
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif	
};
