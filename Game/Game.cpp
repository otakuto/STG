#pragma once
#include "stdafx.hpp"
#include "Game.hpp"
#include "BulletManager.hpp"
#include "DirectGraphics.hpp"
#include "Player.hpp"
#include "IDrawable.hpp"
#include "IRunnable.hpp"
#include "Sprite.hpp"
#include "Enemy.hpp"
#include "StatusFrame.hpp"
#include "CollisionManager.hpp"
#include "EnemyManager.hpp"
#include "Stage.hpp"
#include "Effect.hpp"

int const Game::WINDOW_WIDTH = 800;
int const Game::WINDOW_HEIGHT = 600;
int const Game::OBJECT_ENABLED_WIDTH = 400;
int const Game::OBJECT_ENABLED_HEIGHT = 600;

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
	for (auto iterator : iRunnableList)
	{
		SAFE_DELETE(iterator);
	}
}

void Game::Run()
{
	directInput.Run();

	for (auto const iterator : iRunnableList)
	{
		iterator->Run();
	}

	LPDIRECT3DDEVICE9 const device = directGraphics.Device();

	device->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_XRGB(0xFF, 0xFF, 0xFF), 1.0, 0);
	device->BeginScene();

	for (auto const iterator : iDrawableList)
	{
		iterator->Draw();
	}

	device->EndScene();
	device->Present(nullptr, nullptr, nullptr, nullptr);
}

