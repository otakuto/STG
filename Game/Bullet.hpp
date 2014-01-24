#pragma once
#include "stdafx.hpp"
#include "DirectGraphics.hpp"
#include "Sprite.hpp"
#include "IDrawable.hpp"
#include "IRunnable.hpp"

class Bullet : public IDrawable, public IRunnable
{
public:
	typedef std::function<void (D3DXVECTOR3 &position, D3DXVECTOR3 &speed, const unsigned long long &time)> BulletOrbit;

public:
	Bullet(const std::shared_ptr<const Sprite> sprite, const BulletOrbit &bulletOrbit, const D3DXVECTOR3 &position, const D3DXVECTOR3 &speed, const float radius, const float angle);
	~Bullet();

public:
	const bool Enabled() const;
	void Enabled(const bool enabled);
	const float Radius() const;
	const D3DXVECTOR3 &Position() const;
	const float Angle() const;
	void Angle(const float angle);
public:
	void Draw() const override;
	void Run() override;

protected:
	const std::shared_ptr<const Sprite> sprite;
	const BulletOrbit bulletOrbit;
	D3DXVECTOR3 position;
	D3DXVECTOR3 speed;
	unsigned long long time;
	bool enabled;
	float radius;
	float angle;
};
