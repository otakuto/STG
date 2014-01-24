#pragma once
#include "stdafx.h"
#include "CollisionManager.h"
#include "BulletManager.h"
#include "Player.h"

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
	for (auto bullet = playerBulletList.begin(); bullet != playerBulletList.end(); ++bullet)
	{
		for (auto enemy = enemyList.begin(); enemy != enemyList.end(); ++enemy)
		{
			if (D3DXVec3Length(&((*bullet)->Position() - (*enemy)->Position())) < (*bullet)->Radius() + (*enemy)->Radius())
			{
				(*bullet)->Enabled(false);
				(*enemy)->Damage(1);
			}
		}
	}
	//return
	for (auto enemy = enemyList.begin(); enemy != enemyList.end(); ++enemy)
	{
		if (D3DXVec3Length(&((*enemy)->Position() - player.Position())) < (*enemy)->Radius() + player.Radius())
		{
			(*enemy)->Damage(1);
			player.Life(0);
		}
	}

	for (auto bullet = enemyBulletList.begin(); bullet != enemyBulletList.end(); ++bullet)
	{
		if (D3DXVec3Length(&((*bullet)->Position() - player.Position())) < (*bullet)->Radius() + player.Radius())
		{
			(*bullet)->Enabled(false);
			player.Life(0);
		}
	}
}
