#pragma once
#include "Enemy.h"
#include "IRunnable.h"
#include "IDrawable.h"

class EnemyManager : public IRunnable, public IDrawable
{
public:
	EnemyManager();
	~EnemyManager();

public:
	void Run() override;
	void Draw() const override;

public:
	std::list<Enemy*> &EnemyList();

protected:
	std::list<Enemy*> enemyList;
};
