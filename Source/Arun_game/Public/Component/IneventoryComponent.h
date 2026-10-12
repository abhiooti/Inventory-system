// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IneventoryComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);
class UItemBase;

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "No Item Is Added"),
	IAR_PartialAmountItemAdded UMETA(DisplayName = "Partial Amount Is Added"),
	IAR_AllItemAdded UMETA(DisplayName = "All Items Added"),
};

USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY();
	FItemAddResult() : ActualAmountAdded(0),OperationResult(EItemAddResult::IAR_NoItemAdded),
	ResultMessage(FText::GetEmpty()){};
	
	UPROPERTY(BlueprintReadOnly,Category="Item add result")
	int32 ActualAmountAdded;
	
	UPROPERTY(BlueprintReadOnly,Category="Item add result")
	EItemAddResult OperationResult;
	
	UPROPERTY(BlueprintReadOnly,Category="Item add result")
	FText ResultMessage;
	
	static FItemAddResult AddNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneReuslt;
		
		AddedNoneReuslt.ActualAmountAdded = 0;
		AddedNoneReuslt.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneReuslt.ResultMessage = ErrorText;
		
		return AddedNoneReuslt;
	};
	static FItemAddResult AddPartial(const int32 PartialAmountAdded, const FText& ErrorText)
	{
		FItemAddResult AddedPartialReuslt;
		AddedPartialReuslt.ActualAmountAdded = 0;
		AddedPartialReuslt.OperationResult = EItemAddResult::IAR_PartialAmountItemAdded;
		AddedPartialReuslt.ResultMessage = ErrorText;
		
		return AddedPartialReuslt;
	}
	static FItemAddResult AddAll(const int32 AmountAdded,const FText& Message)
	{
		FItemAddResult AddedAllReuslt;
		
		AddedAllReuslt.ActualAmountAdded = AmountAdded;
		AddedAllReuslt.OperationResult = EItemAddResult::IAR_AllItemAdded;
		AddedAllReuslt.ResultMessage = Message;
		
		return AddedAllReuslt;
	}
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARUN_GAME_API UIneventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	FOnInventoryUpdated OnInventoryUpdated;
	// Sets default values for this component's properties
	UIneventoryComponent();
	
	UFUNCTION(Category="Invnettory")
	UItemBase* findMatchingItem(UItemBase* ItemIn) const;
	
	UFUNCTION(Category="Invnettory")
	UItemBase* findNextItemByID(UItemBase* ItemIn) const;
	
	UFUNCTION(Category="Invnettory")
	UItemBase* findPartialStack(UItemBase* ItemIn) const;
	
	UFUNCTION(Category="Invnettory")
	FItemAddResult HandleAddItem(UItemBase* InputItem);
	
	UFUNCTION(Category="Invnettory")
	void RemoveSingleInstanceOfItem(UItemBase* ItemIn);
	
	UFUNCTION(Category="Invnettory")
	int32 RemoveAmountItem(UItemBase* ItemIn,int32 DesiredAmountToRemove);
	
	UFUNCTION(Category="Invnettory")
	void SplitExisistingStack(UItemBase* ItemIn,int32 AmountToSplit);
	
	//Gettters
	//-----------------------------------
	UFUNCTION(Category="Invnettory")
	FORCEINLINE float GetInventoryTotalWeight() const { return InventoryTotalWeight; };
	
	UFUNCTION(Category="Invnettory")
	FORCEINLINE float GetInventoryCapacity() const { return InventoryWeightCapacity;};
	
	UFUNCTION(Category="Invnettory")
	FORCEINLINE int32 GetSlotCapacity() const { return InventorySlotCapacity; };
	
	UFUNCTION(Category="Invnettory")
	FORCEINLINE TArray<UItemBase*> GetInevntoryContents() const { return InventoryContents; };
	
	//Setters
	//-------------------------------------
	UFUNCTION(Category="Invnettory")
	FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCapacity) { InventorySlotCapacity = NewSlotsCapacity; };
	
	UFUNCTION(Category="Invnettory")
	FORCEINLINE void SetWeightCapacity(const int32 NewWeightCapacity) { InventoryWeightCapacity = NewWeightCapacity; };
	
	

protected:
	
	UPROPERTY(VisibleAnywhere,Category="Invnettory")
	float InventoryTotalWeight;
	
	UPROPERTY(EditDefaultsOnly,Category="Invnettory")
	int32 InventorySlotCapacity;
	
	UPROPERTY(VisibleAnywhere,Category="Invnettory")
	float InventoryWeightCapacity;
	
	UPROPERTY(VisibleAnywhere,Category="Invnettory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;

	
	// Called when the game starts
	virtual void BeginPlay() override;
	
	FItemAddResult HandleNonStackbleItems(UItemBase*, int32 RequestedAddAmount);
	int32 HandleStackableItems(UItemBase*, int32 RequestedAddAmount);
	int32 CalucalteWeghitAddAmount(UItemBase*, int32 RequestedAddAmount);
	int32 CalculateNumberForFullStack(UItemBase* ExisitingItem, int32 IntitalRequestedAddAmount);
	
	void AddNewItem(UItemBase* Item,const int32 AmountAdd);
};
