#pragma once
#include "stdafx.hpp"

class IPosition
{
public:
	virtual ~IPosition();

public:
	virtual D3DXVECTOR3 &Position() = 0;
	virtual void Position(D3DXVECTOR3 const&position) = 0;
};

