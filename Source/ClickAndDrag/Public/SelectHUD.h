// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SelectHUD.generated.h"

/**
 * 
 */
UCLASS()
class CLICKANDDRAG_API ASelectHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void DrawHUD() override;
	virtual void ToggleDrawBox(bool IsSelecting);
	virtual void SetBoxStartPos(float StartX,float StartY);
	virtual void SetBoxEndPos(float EndX,float EndY);
	virtual TArray<AActor*> GetSelected();

private:
	FColor LineColour = FColor::White;
	float LineWidth = 1.0f;

public:
	float m_StartX;
	float m_StartY;
	float m_EndX;
	float m_EndY;
	TArray<AActor*> SelectedActors;
	bool m_IsSelecting = false;
};
