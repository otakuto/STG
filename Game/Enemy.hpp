#pragma once
#include "stdafx.hpp"
#include "IDrawable.hpp"
#include "IRunnable.hpp"
#include "DirectGraphics.hpp"
#include "DirectInput.hpp"
#include "IGameObject.hpp"
#include "BulletManager.hpp"
#include "Sprite.hpp"
#include "IRadiusGettable.hpp"

class Enemy : public IDrawable, public IRunnable, public IGameObject
{
public:
	typedef boost::coroutines::coroutine<void()> Routine;
public:
	Enemy(std::shared_ptr<Sprite const> sprite, std::function<void(Routine::caller_type &, Enemy &)> const routine, D3DXVECTOR3 const & position, float const radius, int const life);
	~Enemy();

public:
	void Draw() const override;
	void Run() override;
	int const Life() const override;
	void Life(int const life) override;
	D3DXVECTOR3 & Position() override;
	void Position(D3DXVECTOR3 const & position) override;
	float const Radius() const override;

public:
	bool const Enabled() const;
	void Enabled(bool const enabled);
	void Damage(int const damage);

protected:
	std::shared_ptr<Sprite const> sprite;
	Routine routine;
	D3DXVECTOR3 position;
	float radius;
	float angle;
	int life;
	bool enabled;
};
