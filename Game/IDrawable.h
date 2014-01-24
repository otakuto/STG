#pragma once
#include "stdafx.h"

class IDrawable
{
public:
	virtual ~IDrawable();

public:
	virtual void Draw() const = 0;
};
