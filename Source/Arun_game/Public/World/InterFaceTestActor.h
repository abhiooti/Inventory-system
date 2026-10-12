// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterFaces/Interactioninterface.h"
#include "InterFaceTestActor.generated.h"

UCLASS()
class ARUN_GAME_API AInterFaceTestActor : public AActor ,public  IInteractioninterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterFaceTestActor();
	
	UPROPERTY(EditAnywhere,Category="Test Actor")
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditInstanceOnly,Category="Test Actor") 
	FInteractabledata InstanceInteractabledata;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	virtual void BeginInteraction() override;
	virtual void EndInteraction() override;
	virtual void Interact(AArun_Character* player) override;
};
