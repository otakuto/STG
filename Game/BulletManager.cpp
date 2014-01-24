#pragma once
#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "IGameObject.h"

BulletManager::BulletManager()
	:
	bulletList(std::list<Bullet*>())
{
}

BulletManager::~BulletManager()
{
	for (auto iterator = bulletList.begin(); iterator != bulletList.end(); ++iterator)
	{
		delete &**iterator;
	}
}

void BulletManager::Draw() const
{
	for (auto iterator = bulletList.begin(); iterator != bulletList.end(); ++iterator)
	{
		(*iterator)->Draw();
	}
}

void BulletManager::Run()
{
	for (auto iterator = bulletList.begin(); iterator != bulletList.end();)
	{
		if ((*iterator)->Enabled())
		{
			(*iterator)->Run();
			++iterator;
		}
		else
		{
			delete *iterator;
			iterator = bulletList.erase(iterator);
		}
	}
}

std::list<Bullet*> &BulletManager::BulletList()
{
	return bulletList;
}
