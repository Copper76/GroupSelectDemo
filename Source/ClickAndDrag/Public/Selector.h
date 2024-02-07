// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "SelectHUD.h"
#include "Selector.generated.h"

UCLASS()
class CLICKANDDRAG_API ASelector : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASelector();

private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SelectAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UMaterial* NormalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UMaterial* SelectedMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleSelect(const FInputActionValue& Value);

private:
	TArray<AActor*> SelectedActors;
	TArray<AActor*> PreviouslySelectedActors;

	APlayerController* playerController;
	ASelectHUD* Hud;
};
