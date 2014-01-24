#pragma once
#include "stdafx.h"
#include "IRunnable.h"
#include "IDrawable.h"
#include "Sprite.h"
#include "DirectGraphics.h"

class StatusFrame : public IDrawable, public IRunnable
{
public:
	StatusFrame(const DirectGraphics &directGraphics);
	~StatusFrame();

public:
	void Run() override;
	void Draw() const override;

protected:
	Sprite sprite;
};

