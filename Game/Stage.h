#pragma once
#include "stdafx.h"
#include "Bullet.h"
#include "Enemy.h"
#include "IRunnable.h"
#include "Player.h"

class Stage : public IRunnable
{
public:
	Stage(std::function<void(boost::coroutines::coroutine<void()>::caller_type&)> &routine);
	Stage(const DirectGraphics &directGraphics, Player &player, std::list<Bullet*> &playerBulletList, std::list<Enemy*> &enemyList, std::list<Bullet*> &enemyBulletList);
	~Stage();

public:
	void Run() override;
	
public:
	boost::coroutines::coroutine<void()> routine;

protected:
	std::shared_ptr<std::vector<std::shared_ptr<Sprite>>> bulletSprite;
	std::shared_ptr<std::vector<std::shared_ptr<Sprite>>> enemySprite;
	std::shared_ptr<std::vector<Bullet::BulletOrbit>> bulletOrbit;
	std::shared_ptr<std::vector<std::function<void(D3DXVECTOR3 &position)>>> barrage;
	std::shared_ptr<std::vector<std::function<void(Enemy::Routine::caller_type&, Enemy&)>>> enemyRoutine;
};