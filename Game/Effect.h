#pragma once
#include "stdafx.h"
#include "IRunnable.h"
#include "IDrawable.h"

class Effect : public IRunnable, public IDrawable
{
public:
	Effect();
	~Effect();

public:
	void Run() override;
	void Draw() const override;

public:
	const bool Enabled() const;
	void Enabled(const bool enabled);

protected:
	bool enabled;
};
