#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletManager.h"

class CollisionManager : public IRunnable
{
public:
	CollisionManager(Player &player, std::list<Bullet*> &playerBulletList, std::list<Enemy*> &enemyList, std::list<Bullet*> &enemyBulletList);
	~CollisionManager();

public:
	void Run() override;

protected:
	Player &player;
	std::list<Bullet*> &playerBulletList;
	std::list<Enemy*> &enemyList;
	std::list<Bullet*> &enemyBulletList;
};

