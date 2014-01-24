#pragma once
#include "stdafx.h"
#include "IDrawable.h"
#include "IRunnable.h"
#include "DirectGraphics.h"
#include "DirectInput.h"
#include "IGameObject.h"
#include "BulletManager.h"
#include "Sprite.h"
#include "IRadiusGettable.h"

class Enemy : public IDrawable, public IRunnable, public IGameObject
{
public:
	typedef boost::coroutines::coroutine<void()> Routine;
public:
	Enemy(std::shared_ptr<const Sprite> sprite, const std::function<void(Routine::caller_type&, Enemy&)> routine, const D3DXVECTOR3 &position, const float radius, const int life);
	~Enemy();

public:
	void Draw() const override;
	void Run() override;
	const int Life() const override;
	void Life(const int life) override;
	D3DXVECTOR3 &Position() override;
	void Position(const D3DXVECTOR3 &position) override;
	const float Radius() const override;

public:
	const bool Enabled() const;
	void Enabled(const bool enabled);
	void Damage(const int damage);

protected:
	std::shared_ptr<const Sprite> sprite;
	Routine routine;
	D3DXVECTOR3 position;
	float radius;
	float angle;
	int life;
	bool enabled;
};
