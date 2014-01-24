#pragma once
#include "stdafx.hpp"
#include "StatusFrame.hpp"
#include "DirectGraphics.hpp"

StatusFrame::StatusFrame(const DirectGraphics &directGraphics)
:
sprite(directGraphics.Device(), TEXT("statusFrame.png"), RECT{0, 0, 400, 600}, D3DXVECTOR3(0, 0, 0), false)
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