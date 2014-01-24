#pragma once
#include "stdafx.h"

class ILife
{
public:
	virtual ~ILife();

public:
	virtual const int Life() const = 0;
	virtual void Life(const int life) = 0;
};

