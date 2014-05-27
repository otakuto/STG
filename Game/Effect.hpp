#pragma once
#include "stdafx.hpp"
#include "IRunnable.hpp"
#include "IDrawable.hpp"

class Effect
	:
	public IRunnable,
	public IDrawable
{
public:
	Effect();
	~Effect();

public:
	void Run() override;
	void Draw() const override;

public:
	bool const Enabled() const;
	void Enabled(bool const enabled);

protected:
	bool enabled;
};
