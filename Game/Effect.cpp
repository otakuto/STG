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

bool const Effect::Enabled() const
{
	return enabled;
}

void Effect::Enabled(bool const enabled)
{
	this->enabled = enabled;
}
