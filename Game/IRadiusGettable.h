#pragma once
#include "stdafx.h"

class IRadiusGettable
{
public:
	virtual ~IRadiusGettable();

public:
	virtual const float Radius() const = 0;
};
