// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InterFaces/Interactioninterface.h"
#include "Arun_Character.generated.h"

class AGameHUD;

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY();
	
	FInteractionData() : CurrentInterActable(nullptr), LastInteractionCheckTime(0.0f)
	{
		
	};
	UPROPERTY()
	AActor* CurrentInterActable;
	
	UPROPERTY()
	float LastInteractionCheckTime;
	
};
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class ARUN_GAME_API AArun_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArun_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,Category="Interaction")
	TScriptInterface<IInteractioninterface> TargetInteractble;
	
	float Interactioncheckfrequncy;
	
	float intractionchechdistance;
	
	FTimerHandle TimerHandle_Interaction;
	
	FInteractionData InteractionData;
	
	void PerformInteractionCheck();
	void interactioncheck(AActor* NewInterActable);
	void NointeractionFound();
	void EndInteract();
	void BeginInteraction();
	void Interact();
	
	UPROPERTY()
	AGameHUD* HUD;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void Jump();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess="true"))
	UCameraComponent* Camera;
	
	FORCEINLINE bool IsInteracting() const
	{
		return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction);
	}

};
