#pragma once
#include "stdafx.hpp"
#include "IRunnable.hpp"
#include "IDrawable.hpp"
#include "Sprite.hpp"
#include "DirectGraphics.hpp"

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

