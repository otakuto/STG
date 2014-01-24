#pragma once
#include "stdafx.h"
#include "Bullet.h"
#include "IDrawable.h"
#include "IRunnable.h"
#include "IGameObject.h"

class BulletManager : public IDrawable, public IRunnable
{
public:
	BulletManager();
	~BulletManager();

public:
	void Draw() const override;
	void Run() override;

public:
	std::list<Bullet*> &BulletList();

protected:
	std::list<Bullet*> bulletList;
};
