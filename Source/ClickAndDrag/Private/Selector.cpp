// Fill out your copyright notice in the Description page of Project Settings.


#include "Selector.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/HUD.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ASelector::ASelector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASelector::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Hud = Cast<ASelectHUD>(playerController->GetHUD());
}

void ASelector::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Sprinting
		EnhancedInputComponent->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ASelector::ToggleSelect);
	}
}

// Called every frame
void ASelector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Hud->m_IsSelecting)
	{
		float X, Y;
		playerController->GetMousePosition(X, Y);
		Hud->SetBoxEndPos(X, Y);
	}

}

void ASelector::ToggleSelect(const FInputActionValue& Value)
{
	//Start the selection process
	if (Value.Get<bool>()) {
		PreviouslySelectedActors = SelectedActors;
		float X, Y;
		playerController->GetMousePosition(X,Y);
		UE_LOG(LogTemp, Warning, TEXT("Mouse Location: %f,%f"), X, Y);
		Hud->SetBoxStartPos(X, Y);
		Hud->SetBoxEndPos(X, Y);
		Hud->ToggleDrawBox(true);
	}
	else//finalise the selection
	{
		SelectedActors = Hud->GetSelected();
		for (AActor* actor : PreviouslySelectedActors) {
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *actor->GetActorLabel());
			UStaticMeshComponent* visualComponent = actor->GetComponentByClass<UStaticMeshComponent>();
			visualComponent->SetMaterial(0, NormalMaterial);
		}
		for(AActor * actor : SelectedActors) {
			UE_LOG(LogTemp, Warning, TEXT("%s"),*actor->GetActorLabel());
			UStaticMeshComponent* visualComponent = actor->GetComponentByClass<UStaticMeshComponent>();
			visualComponent->SetMaterial(0, SelectedMaterial);
		}
		Hud->ToggleDrawBox(false);
	}
}

