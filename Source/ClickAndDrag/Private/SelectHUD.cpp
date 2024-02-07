// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectHUD.h"
#include "Engine/Canvas.h"
#include "Ball.h"

void ASelectHUD::DrawHUD()
{
    Super::DrawHUD();

    // Get the Canvas
    if (Canvas)
    {
        if (m_IsSelecting)
        {
            DrawLine(m_StartX, m_StartY, m_EndX, m_StartY, LineColour, LineWidth);
            DrawLine(m_StartX, m_StartY, m_StartX, m_EndY, LineColour, LineWidth);
            DrawLine(m_EndX, m_StartY, m_EndX, m_EndY, LineColour, LineWidth);
            DrawLine(m_StartX, m_EndY, m_EndX, m_EndY, LineColour, LineWidth);
            SelectedActors.Empty();
            GetActorsInSelectionRectangle(FVector2D(m_StartX, m_StartY), FVector2D(m_EndX, m_EndY), SelectedActors, false, false);
        }
    }
}

void ASelectHUD::ToggleDrawBox(bool IsSelecting)
{
    m_IsSelecting = IsSelecting;
}

void ASelectHUD::SetBoxStartPos(float StartX, float StartY)
{
    m_StartX = StartX;
    m_StartY = StartY;
}

void ASelectHUD::SetBoxEndPos(float EndX, float EndY)
{
    m_EndX = EndX;
    m_EndY = EndY;
}

TArray<AActor*> ASelectHUD::GetSelected()
{
    TArray<AActor*> OutActors = TArray<AActor*>();
    for (AActor* actor : SelectedActors)
    {
        if (actor->Tags.Contains("Selectable"))
        {
            OutActors.Add(actor);
        }
    }
    return OutActors;
}