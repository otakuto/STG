#pragma once
#include "stdafx.h"
#include "Game.h"
#include "BulletManager.h"
#include "DirectGraphics.h"
#include "Player.h"
#include "IDrawable.h"
#include "IRunnable.h"
#include "Sprite.h"
#include "Enemy.h"
#include "StatusFrame.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "Stage.h"
#include "Effect.h"

const int Game::WINDOW_WIDTH = 800;
const int Game::WINDOW_HEIGHT = 600;
const int Game::OBJECT_ENABLED_WIDTH = 400;
const int Game::OBJECT_ENABLED_HEIGHT = 600;

Game::Game(const HWND &hWnd)
:
directGraphics(hWnd),
directInput(hWnd),
iRunnableList(),
iDrawableList()
{
	BulletManager *playerBulletManager = new BulletManager();
	iRunnableList.push_back(playerBulletManager);
	iDrawableList.push_back(playerBulletManager);

	Player *player = new Player(directGraphics, directInput.Key(), *playerBulletManager);
	iRunnableList.push_back(player);
	iDrawableList.push_back(player);

	BulletManager *enemyBulletManager = new BulletManager();
	iRunnableList.push_back(enemyBulletManager);
	iDrawableList.push_back(enemyBulletManager);

	EnemyManager *enemyManager = new EnemyManager();
	iRunnableList.push_back(enemyManager);
	iDrawableList.push_back(enemyManager);

	CollisionManager *collisionManager = new CollisionManager(*player, playerBulletManager->BulletList(), enemyManager->EnemyList(), enemyBulletManager->BulletList());
	iRunnableList.push_back(collisionManager);
	{
		Stage *stage = new Stage(directGraphics, *player, playerBulletManager->BulletList(), enemyManager->EnemyList(), enemyBulletManager->BulletList());
		iRunnableList.push_back(stage);
	}
	StatusFrame *statusFrame = new StatusFrame(directGraphics);
	iRunnableList.push_back(statusFrame);
	iDrawableList.push_back(statusFrame);
}

Game::~Game()
{
	for (auto iterator = iRunnableList.begin(); iterator != iRunnableList.end(); ++iterator)
	{
		SAFE_DELETE(*iterator);
	}
}

void Game::Run()
{
	directInput.Run();

	for (auto iterator = iRunnableList.begin(); iterator != iRunnableList.end(); ++iterator)
	{
		(*iterator)->Run();
	}

	const LPDIRECT3DDEVICE9 device = directGraphics.Device();

	device->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF), 1.0, 0);
	device->BeginScene();

	for (auto iterator = iDrawableList.begin(); iterator != iDrawableList.end(); ++iterator)
	{
		(*iterator)->Draw();
	}

	device->EndScene();
	device->Present(nullptr, nullptr, nullptr, nullptr);
}

