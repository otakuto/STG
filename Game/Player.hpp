#pragma once
#include "stdafx.hpp"
#include "DirectGraphics.hpp"
#include "DirectInput.hpp"
#include "Sprite.hpp"
#include "BulletManager.hpp"
#include "IRunnable.hpp"
#include "IDrawable.hpp"
#include "IGameObject.hpp"
#include "IRadiusGettable.hpp"

class Player : public IDrawable, public IRunnable, public IGameObject
{
public:
	Player(const DirectGraphics &directGraphics, const std::vector<unsigned char> &key, BulletManager &bulletManager);
	~Player();

public:
	void Draw() const override;
	void Run() override;

public:
	int const Life() const override;
	void Life(int const life) override;
	D3DXVECTOR3 &Position() override;
	void Position(D3DXVECTOR3 const&position) override;
	float const Radius() const override;

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

