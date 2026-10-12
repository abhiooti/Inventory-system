// Fill out your copyright notice in the Description page of Project Settings.


#include "Arun_game/Public/Player/Arun_Character.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "UserInterface/GameHUD.h"

// Sets default values
AArun_Character::AArun_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	
	Interactioncheckfrequncy = 0.1;
	intractionchechdistance = 225.0f;
}

// Called when the game starts or when spawned
void AArun_Character::BeginPlay()
{
	Super::BeginPlay();
	
	HUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
}

void AArun_Character::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();
	
	FVector TraceStart{GetPawnViewLocation()};
	FVector TraceEnd{TraceStart + (GetViewRotation().Vector() * intractionchechdistance)};
	
	double lookDirection = FVector::DotProduct(GetActorForwardVector(),GetViewRotation().Vector());
	if (lookDirection > 0)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 10.0f);
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		FHitResult TraceHit;
	
		if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd,ECC_Visibility,QueryParams))
		{
			if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractioninterface::StaticClass()))
			{
				const float Distance = (TraceStart - TraceHit.ImpactPoint).Size();
			
				if (TraceHit.GetActor() != InteractionData.CurrentInterActable && Distance <= intractionchechdistance)
				{
					interactioncheck(TraceHit.GetActor());
					return;
				}
				if (TraceHit.GetActor() == InteractionData.CurrentInterActable)
				{
					return;
				}
			}
		}
	}
		NointeractionFound();
	}

void AArun_Character::interactioncheck(AActor* NewInterActable)
{
	if (IsInteracting())
	{
		EndInteract();
	}
	if (InteractionData.CurrentInterActable)
	{
		TargetInteractble = InteractionData.CurrentInterActable;
		TargetInteractble->EndFocus();
	}
	InteractionData.CurrentInterActable = NewInterActable;
	TargetInteractble = NewInterActable;
	
	HUD->UpdateInteractionWidget(&TargetInteractble->Interactable);
	TargetInteractble ->BeginFocus();
}

void AArun_Character::NointeractionFound()
{
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}
	if (InteractionData.CurrentInterActable)
	{
		if (IsValid(TargetInteractble.GetObject()))
		{
			TargetInteractble->EndFocus();
		}
		HUD->HideInteractionWidget();
		InteractionData.CurrentInterActable = nullptr;
		TargetInteractble = nullptr;
	}
	
}
void AArun_Character::BeginInteraction()
{
	PerformInteractionCheck();
	
	if (InteractionData.CurrentInterActable)
	{
		if (IsValid(TargetInteractble.GetObject()))
		{
			TargetInteractble->BeginInteraction();
			
			if (FMath::IsNearlyZero(TargetInteractble->Interactable.InterActionDuration,0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction,this,
					&AArun_Character::Interact,
					TargetInteractble->Interactable.InterActionDuration,
					false);
			}
		}
	}
}
void AArun_Character::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	if (IsValid(TargetInteractble.GetObject()))
	{
		TargetInteractble->EndInteraction();
	}
}

void AArun_Character::Interact()
{
	if (IsValid(TargetInteractble.GetObject()))
	{
		TargetInteractble->Interact(this);
	}
}

// Called every frame
void AArun_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > Interactioncheckfrequncy)
	{
		PerformInteractionCheck();
	}
	

}



// Called to bind functionality to input
void AArun_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AArun_Character::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AArun_Character::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AArun_Character::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AArun_Character::LookUp);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AArun_Character::Jump);
	PlayerInputComponent->BindAction(TEXT("Interaction"),IE_Pressed,this,&AArun_Character::BeginInteraction);
	PlayerInputComponent->BindAction(TEXT("Interaction"),IE_Released,this,&AArun_Character::EndInteract);
}

void AArun_Character::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void AArun_Character::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void AArun_Character::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AArun_Character::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AArun_Character::Jump()
{
	ACharacter::Jump();
}

