#pragma once
#include "stdafx.hpp"
#include "Bullet.hpp"
#include "DirectGraphics.hpp"
#include "Game.hpp"
#include "Sprite.hpp"
#include "IDrawable.hpp"
#include "IRunnable.hpp"

Bullet::Bullet(std::shared_ptr<Sprite const> const sprite, BulletOrbit const & bulletOrbit, D3DXVECTOR3 const & position, D3DXVECTOR3 const & speed, float const radius, float const angle)
	:
	sprite(sprite),
	bulletOrbit(bulletOrbit),
	position(position),
	speed(speed),
	time(0),
	enabled(true),
	radius(radius),
	angle(angle)
{
}

Bullet::~Bullet()
{
}

bool const Bullet::Enabled() const
{
	return enabled;
}

void Bullet::Enabled(bool const enabled)
{
	this->enabled = enabled;
}

float const Bullet::Radius() const
{
	return radius;
}

D3DXVECTOR3 const & Bullet::Position() const
{
	return position;
}

float const Bullet::Angle() const
{
	return angle;
}

void Bullet::Angle(float const angle)
{
	this->angle = angle;
}

void Bullet::Draw() const
{
	sprite->Draw(position, angle);
}

void Bullet::Run()
{
	if ((0 <= position.x) && (position.x < Game::OBJECT_ENABLED_WIDTH) && (0 <= position.y) && (position.y < Game::OBJECT_ENABLED_HEIGHT))
	{
		bulletOrbit(position, speed, time);
		++time;
	}
	else
	{
		enabled = false;
	}
}
