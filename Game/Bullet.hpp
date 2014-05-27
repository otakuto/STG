#pragma once
#include "stdafx.hpp"
#include "DirectGraphics.hpp"
#include "Sprite.hpp"
#include "IDrawable.hpp"
#include "IRunnable.hpp"

class Bullet
	:
	public IDrawable,
	public IRunnable
{
public:
	using BulletOrbit = std::function<void(D3DXVECTOR3 & position, D3DXVECTOR3 & speed, unsigned long long const time)>;

public:
	Bullet(std::shared_ptr<Sprite const> const sprite, BulletOrbit const & bulletOrbit, D3DXVECTOR3 const & position, D3DXVECTOR3 const & speed, float const radius, float const angle);
	~Bullet();

public:
	bool const Enabled() const;
	void Enabled(bool const enabled);
	float const Radius() const;
	D3DXVECTOR3 const & Position() const;
	float const Angle() const;
	void Angle(float const angle);
public:
	void Draw() const override;
	void Run() override;

protected:
	std::shared_ptr<Sprite const> const sprite;
	BulletOrbit const bulletOrbit;
	D3DXVECTOR3 position;
	D3DXVECTOR3 speed;
	unsigned long long time;
	bool enabled;
	float radius;
	float angle;
};
