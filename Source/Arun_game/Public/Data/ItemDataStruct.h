#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStruct.generated.h"

UENUM()
enum class EItemQuality : uint8
{
	firstphase UMETA(DisplayName = "FirstPhase"),
	secondphase UMETA(DisplayName = "SecondPhase"),
	thirdphase UMETA(DisplayName ="ThirdPhase"),
	fourthphase UMETA(Displaname = "FourthPhase"),
	legend UMETA(DisplayNAme = "Legend"),
};

UENUM()
enum class EItemtype : uint8
{
	
	Armar UMETA(DisplayName = "Armar"),
	Wepone UMETA(DisplayNAme = "Wepone"),
	Shield UMETA(DisplaName = "Shield"),
	Spell UMETA(DisplayName = "Spell"),
	Consumble UMETA(DisplayNAme = "Consumble"),
	Quste UMETA(DisplayName = "Quste"),
	Muden UMETA(DisplayNAme = "Mudenn")
};

USTRUCT()
struct FItemNumeracData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	float Weight;
	
	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;
	
	UPROPERTY(EditAnywhere)
	bool bIsStackable;
	
};

USTRUCT()
struct FItemAssetData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;
	
	UPROPERTY(EditAnywhere)
	UStaticMesh* StaticMesh;
};


USTRUCT()
struct FItemStatistcis
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	float ArmorRatating;
	
	UPROPERTY(EditAnywhere)
	float DamageVlaue;
	
	UPROPERTY(EditAnywhere)
	float RestorationAmount;
	
	UPROPERTY(EditAnywhere)
	float sellvalue;
};

USTRUCT()
struct FItemTextData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	FText Name;
	
	UPROPERTY(EditAnywhere)
	FText Description;
	
	UPROPERTY(EditAnywhere)
	FText InteractionText;
	
	UPROPERTY(EditAnywhere)
	FText UsageText;
	
};
USTRUCT()
struct  FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
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
};
