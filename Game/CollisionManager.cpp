#pragma once
#include "stdafx.hpp"
#include "CollisionManager.hpp"
#include "BulletManager.hpp"
#include "Player.hpp"

CollisionManager::CollisionManager(Player &player, std::list<Bullet*> &playerBulletList, std::list<Enemy*> &enemyList, std::list<Bullet*> &enemyBulletList)
	:
	player(player),
	playerBulletList(playerBulletList),
	enemyList(enemyList),
	enemyBulletList(enemyBulletList)
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::Run()
{
	for (auto const bullet : playerBulletList)
	{
		for (auto const enemy : enemyList)
		{
			if (D3DXVec3Length(&(bullet->Position() - enemy->Position())) < bullet->Radius() + enemy->Radius())
			{
				bullet->Enabled(false);
				enemy->Damage(1);
			}
		}
	}
	
	for (auto const enemy : enemyList)
	{
		if (D3DXVec3Length(&(enemy->Position() - player.Position())) < enemy->Radius() + player.Radius())
		{
			enemy->Damage(1);
			player.Life(0);
		}
	}

	for (auto const bullet : enemyBulletList)
	{
		if (D3DXVec3Length(&(bullet->Position() - player.Position())) < bullet->Radius() + player.Radius())
		{
			bullet->Enabled(false);
			player.Life(0);
		}
	}
}
