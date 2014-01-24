#pragma once
#include "stdafx.hpp"
#include "Stage.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Player.hpp"

Stage::Stage(const DirectGraphics &directGraphics, Player &player, std::list<Bullet*> &playerBulletList, std::list<Enemy*> &enemyList, std::list<Bullet*> &enemyBulletList)
{
	bulletSprite = std::make_shared<std::vector<std::shared_ptr<Sprite>>>();
	bulletSprite->push_back(std::make_shared<Sprite>(directGraphics.Device(), TEXT("Resource/Bullet/000.png"), RECT{0, 0, 8, 8}, D3DXVECTOR3(3, 3, 0), false));
	bulletSprite->push_back(std::make_shared<Sprite>(directGraphics.Device(), TEXT("Resource/Bullet/001.png"), RECT{0, 0, 15, 15}, D3DXVECTOR3(7, 7, 0), false));

	enemySprite = std::make_shared<std::vector<std::shared_ptr<Sprite>>>();
	enemySprite->push_back(std::make_shared<Sprite>(directGraphics.Device(), TEXT("Resource/Enemy/000.png"), RECT{0, 0, 31, 31}, D3DXVECTOR3(15, 15, 0), false));
	enemySprite->push_back(std::make_shared<Sprite>(directGraphics.Device(), TEXT("Resource/Enemy/001.png"), RECT{0, 0, 31, 31}, D3DXVECTOR3(15, 15, 0), false));
	enemySprite->push_back(std::make_shared<Sprite>(directGraphics.Device(), TEXT("Resource/Enemy/002.png"), RECT{0, 0, 31, 31}, D3DXVECTOR3(15, 15, 0), false));
	enemySprite->push_back(std::make_shared<Sprite>(directGraphics.Device(), TEXT("Resource/Enemy/003.png"), RECT{0, 0, 31, 31}, D3DXVECTOR3(15, 15, 0), false));
	enemySprite->push_back(std::make_shared<Sprite>(directGraphics.Device(), TEXT("Resource/Enemy/004.png"), RECT{0, 0, 31, 31}, D3DXVECTOR3(15, 15, 0), false));
	enemySprite->push_back(std::make_shared<Sprite>(directGraphics.Device(), TEXT("Resource/Enemy/005.png"), RECT{0, 0, 31, 31}, D3DXVECTOR3(15, 15, 0), false));

	bulletOrbit = std::make_shared<std::vector<Bullet::BulletOrbit>>();
	bulletOrbit->push_back([&player](D3DXVECTOR3 &position, D3DXVECTOR3 &speed, const unsigned long long time)
	{
		if (!time)
		{
			float angle = std::atan2((player.Position() - position).y, (player.Position() - position).x);
			speed.x *= std::cos(angle);
			speed.y *= std::sin(angle);
		}
		position += speed;
	});
	bulletOrbit->push_back([&player](D3DXVECTOR3 &position, D3DXVECTOR3 &speed, const unsigned long long time)
	{
		if (!time)
		{
			float angle = std::atan2((player.Position() - position).y, (player.Position() - position).x) - std::atan2(D3DXVec3Length(&(player.Position() - position)), static_cast<float>(25)) + D3DXToRadian(90);
			speed.x *= std::cos(angle);
			speed.y *= std::sin(angle);
		}
		position += speed;
	});
	bulletOrbit->push_back([&player](D3DXVECTOR3 &position, D3DXVECTOR3 &speed, const unsigned long long time)
	{
		if (!time)
		{
			float angle = std::atan2((player.Position() - position).y, (player.Position() - position).x) - std::atan2(D3DXVec3Length(&(player.Position() - position)), static_cast<float>(-25)) + D3DXToRadian(90);
			speed.x *= std::cos(angle);
			speed.y *= std::sin(angle);
		}
		position += speed;
	});
	bulletOrbit->push_back([](D3DXVECTOR3 &position, D3DXVECTOR3 &speed, const unsigned long long time)
	{
		position += speed;
	});
	bulletOrbit->push_back([](D3DXVECTOR3 &position, D3DXVECTOR3 &speed, const unsigned long long time)
	{
		speed.y += static_cast<float>(0.01);
		position += speed;
	});

	barrage = std::make_shared<std::vector<std::function<void(D3DXVECTOR3 &position)>>>();
	barrage->push_back([&enemyBulletList, &player, this](D3DXVECTOR3 &position)
	{
		float angle = std::atan2((player.Position() - position).y, (player.Position() - position).x);

		enemyBulletList.push_back(new Bullet((*bulletSprite)[0], (*bulletOrbit)[0], position, D3DXVECTOR3(2, 2, 0), 4, angle));
		enemyBulletList.push_back(new Bullet((*bulletSprite)[0], (*bulletOrbit)[1], position, D3DXVECTOR3(2, 2, 0), 4, angle));
		enemyBulletList.push_back(new Bullet((*bulletSprite)[0], (*bulletOrbit)[2], position, D3DXVECTOR3(2, 2, 0), 4, angle));
	});
	barrage->push_back([&enemyBulletList, this](D3DXVECTOR3 &position)
	{
		float a = static_cast<float>(rand() % 72);
		for (int i = 0; i < 5; ++i)
		{
			float angle = D3DXToRadian((i * 72) + a);
			enemyBulletList.push_back(new Bullet((*bulletSprite)[0], (*bulletOrbit)[3], position, D3DXVECTOR3(std::cos(angle), std::sin(angle), 0), 4, 0));
		}
	});
	barrage->push_back([&enemyBulletList, this](D3DXVECTOR3 &position)
	{
		float a = static_cast<float>(rand() % 18);
		for (int i = 0; i < 20; ++i)
		{
			float angle = D3DXToRadian((i * 18) + a);
			enemyBulletList.push_back(new Bullet((*bulletSprite)[0], (*bulletOrbit)[3], position, D3DXVECTOR3(std::cos(angle), std::sin(angle), 0), 4, 0));
		}
	});

	enemyRoutine = std::make_shared<std::vector<std::function<void(Enemy::Routine::caller_type&, Enemy&)>>>();
	enemyRoutine->push_back([this, &player](Enemy::Routine::caller_type &yield, Enemy &enemy)
	{
		for (int i = 0; i < 50; ++i)
		{
			enemy.Position().y += 2;
			enemy.Position().x += 0.5;
			yield();
		}

		for (int i = 0; i < 3; ++i)
		{
			(*barrage)[0](enemy.Position());
			for (int i = 0; i < 20; ++i)
			{
				yield();
			}
		}

		float angle = atan2((player.Position() - enemy.Position()).y, (player.Position() - enemy.Position()).x);

		D3DXVECTOR3 speed = D3DXVECTOR3(std::cos(angle), std::sin(angle), 0);
		speed *= 1.5;

		while (true)
		{
			enemy.Position() += speed;
			yield();
		};
	});
	enemyRoutine->push_back([this, &player](Enemy::Routine::caller_type &yield, Enemy &enemy)
	{
		for (int i = 0; i < 50; ++i)
		{
			enemy.Position().y += 2;
			enemy.Position().x -= 0.5;
			yield();
		}

		for (int i = 0; i < 3; ++i)
		{
			(*barrage)[0](enemy.Position());
			for (int i = 0; i < 20; ++i)
			{
				yield();
			}
		}

		float angle = atan2((player.Position() - enemy.Position()).y, (player.Position() - enemy.Position()).x);

		D3DXVECTOR3 speed = D3DXVECTOR3(cos(angle), sin(angle), 0);
		speed *= 1.5;

		while (true)
		{
			enemy.Position() += speed;
			yield();
		};
	});

	srand(0);

	routine = boost::coroutines::coroutine<void()>([&enemyList, this, &enemyBulletList](boost::coroutines::coroutine<void()>::caller_type &yield)
	{
		for (int i = 0; i < 10; ++i)
		{
			enemyList.push_back(new Enemy((*enemySprite)[0], (*enemyRoutine)[0], D3DXVECTOR3(static_cast<float>(100 + (i * 10)), 0, 0), static_cast<float>(8), 2));
			for (int j = 0; j < 50; ++j)
			{
				yield();
			}
			enemyList.push_back(new Enemy((*enemySprite)[0], (*enemyRoutine)[1], D3DXVECTOR3(static_cast<float>(300 - (i * 10)), 0, 0), static_cast<float>(8), 2));
			for (int j = 0; j < 80; ++j)
			{
				yield();
			}
		}
		std::mt19937 engine;
		std::uniform_real_distribution<double> distribution(0, std::_Pi * 2);

		for (int y = 0; y < 10; ++y)
		{
			for (int x = 0; x < 10; ++x)
			{
				float angle = distribution(engine);
				enemyBulletList.push_back(new Bullet((*bulletSprite)[0], (*bulletOrbit)[3], D3DXVECTOR3(150 + x, 150 + y, 0), D3DXVECTOR3(std::cos(angle), std::sin(angle), 0), 4, angle));
			}
		}

		while (true)
		{
			yield();
		};
	});
}

Stage::~Stage()
{
}

void Stage::Run()
{
	routine();
}

