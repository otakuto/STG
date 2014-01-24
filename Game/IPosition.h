#pragma once
#include "stdafx.h"

class IPosition
{
public:
	virtual ~IPosition();

public:
	virtual D3DXVECTOR3 &Position() = 0;
	virtual void Position(const D3DXVECTOR3 &position) = 0;
};
