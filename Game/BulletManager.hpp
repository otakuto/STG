#pragma once
#include "stdafx.hpp"
#include "Bullet.hpp"
#include "IDrawable.hpp"
#include "IRunnable.hpp"
#include "IGameObject.hpp"

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
