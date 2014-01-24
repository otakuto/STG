#pragma once
#include "stdafx.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "BulletManager.hpp"

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

