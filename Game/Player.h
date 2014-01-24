#pragma once
#include "stdafx.h"
#include "DirectGraphics.h"
#include "DirectInput.h"
#include "Sprite.h"
#include "BulletManager.h"
#include "IRunnable.h"
#include "IDrawable.h"
#include "IGameObject.h"
#include "IRadiusGettable.h"

class Player : public IDrawable, public IRunnable, public IGameObject
{
public:
	Player(const DirectGraphics &directGraphics, const std::vector<unsigned char> &key, BulletManager &bulletManager);
	~Player();

public:
	void Draw() const override;
	void Run() override;

public:
	const int Life() const override;
	void Life(const int life) override;
	D3DXVECTOR3 &Position() override;
	void Position(const D3DXVECTOR3 &position) override;
	const float Radius() const override;

protected:
	const Sprite sprite;
	std::shared_ptr<const Sprite> spriteBullet;
	const std::vector<unsigned char> &key;
	BulletManager &bulletManager;
	D3DXVECTOR3 position;
	unsigned int life;
	float radius;
	int shotTime;
	int invincibleTime;
};

