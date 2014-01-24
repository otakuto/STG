#pragma once
#include "stdafx.hpp"
#include "Effect.hpp"

Effect::Effect()
:
enabled(true)
{
}

Effect::~Effect()
{
}

void Effect::Run()
{
}

void Effect::Draw() const
{
}

const bool Effect::Enabled() const
{
	return enabled;
}

void Effect::Enabled(const bool enabled)
{
	this->enabled = enabled;
}
