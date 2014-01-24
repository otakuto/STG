#pragma once
#include "stdafx.h"

class IRunnable
{
public:
	virtual ~IRunnable();

public:
	virtual void Run() = 0;
};
