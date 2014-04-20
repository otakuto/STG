#pragma once
#include "stdafx.hpp"

class ILife
{
public:
	virtual ~ILife();

public:
	virtual int const Life() const = 0;
	virtual void Life(int const life) = 0;
};

