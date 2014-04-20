#pragma once
#include "stdafx.hpp"
#include "EnemyManager.hpp"
#include "Enemy.hpp"

EnemyManager::EnemyManager()
	:
	enemyList()
{
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Run()
{
	for (auto iterator = enemyList.begin(); iterator != enemyList.end();)
	{
		if ((*iterator)->Enabled())
		{
			(*iterator)->Run();
			 ++iterator;
		}
		else
		{
			delete *iterator;
			iterator = enemyList.erase(iterator);
		}
	}
}

void EnemyManager::Draw() const
{
	for (auto const iterator : enemyList)
	{
		iterator->Draw();
	}
}

std::list<Enemy*> &EnemyManager::EnemyList()
{
	return enemyList;
}
