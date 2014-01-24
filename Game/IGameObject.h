#pragma once
#include "stdafx.h"
#include "IPosition.h"
#include "ILife.h"
#include "IRadiusGettable.h"

class IGameObject : public IPosition, public ILife, public IRadiusGettable
{
public:
	virtual ~IGameObject();
};
