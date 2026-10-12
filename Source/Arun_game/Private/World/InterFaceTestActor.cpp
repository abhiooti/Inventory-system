// Fill out your copyright notice in the Description page of Project Settings.


#include "World/InterFaceTestActor.h"

// Sets default values
AInterFaceTestActor::AInterFaceTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	SetRootComponent(StaticMesh);
}

// Called when the game starts or when spawned
void AInterFaceTestActor::BeginPlay()
{
	Super::BeginPlay();
	
	Interactable = InstanceInteractabledata;
}

// Called every frame
void AInterFaceTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInterFaceTestActor::BeginFocus()
{
	if (StaticMesh)
	{
		StaticMesh->SetRenderCustomDepth(true);
	}
}

void AInterFaceTestActor::EndFocus()
{
	StaticMesh->SetRenderCustomDepth(false);
}

void AInterFaceTestActor::BeginInteraction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Blue,FString("The the Interaction is begin on the test actor"));
	}
}

void AInterFaceTestActor::EndInteraction()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Blue,FString("The the endInteraction is begin on the test actor"));
	}
}

void AInterFaceTestActor::Interact(AArun_Character* player)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,5,FColor::Blue,FString("The the Interact is begin on the test actor"));
	}
}

