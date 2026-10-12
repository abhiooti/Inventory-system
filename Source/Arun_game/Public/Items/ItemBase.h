// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDataStruct.h"
#include "Player/Arun_Character.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class ARUN_GAME_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	
	//
	//UPROPERTY()
	//UInventoryComponent* OwingInventory;
	
	UPROPERTY(VisibleAnywhere,Category= "Item Data",META = (UIMin=1,UIMax=100))
	int32 Quantity;
	
	UPROPERTY(EditAnywhere,Category= "Item Data")
	FName ID;
	
	UPROPERTY(EditAnywhere,Category= "Item Data")
	FItemAssetData AssetData;
	
	UPROPERTY(EditAnywhere,Category= "Item Data")
	FItemTextData TextDate;
	
	UPROPERTY(EditAnywhere,Category= "Item Data")
	FItemStatistcis Statistcis;
	
	UPROPERTY(EditAnywhere,Category= "Item Data")
	FItemNumeracData NumeracData;
	
	UPROPERTY(EditAnywhere,Category= "Item Data")
	EItemQuality Quality;
	
	UPROPERTY(EditAnywhere,Category= "Item Data")
	EItemtype Type;
	
	//FUNCTIONS
	UItemBase();
	
	UFUNCTION(Category="Item")
	UItemBase* CreateItemCopy() const;
	
	UFUNCTION(Category="Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * NumeracData.Weight; };
	
	UFUNCTION(Category="Item")
	FORCEINLINE float GetItemSingleWeight() const { return NumeracData.Weight; };
	
	UFUNCTION(Category="Item")
	FORCEINLINE bool IsFullitemStack() const { return Quantity == NumeracData.MaxStackSize; };
	
	UFUNCTION(Category="Item")
	FORCEINLINE bool IsEmptyitemStack() const { return Quantity == 0; };
	
	
	void SetQuantity(int32 NewQuantity);
	
	virtual void Use(AArun_Character* Charcater);
	
protected:
	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}
};
