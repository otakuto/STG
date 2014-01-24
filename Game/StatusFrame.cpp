#pragma once
#include "stdafx.h"
#include "StatusFrame.h"
#include "DirectGraphics.h"

StatusFrame::StatusFrame(const DirectGraphics &directGraphics)
:
sprite(directGraphics.Device(), TEXT("statusFrame.png"), RECT_INIT(0, 0, 400, 600), D3DXVECTOR3(0, 0, 0), false)
{
}


StatusFrame::~StatusFrame()
{
}

void StatusFrame::Draw() const
{
	sprite.Draw(D3DXVECTOR3(400, 0, 0));
}

void StatusFrame::Run()
{

}