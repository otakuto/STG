#pragma once
#include "stdafx.hpp"
#include "Bullet.hpp"
#include "DirectGraphics.hpp"
#include "Game.hpp"
#include "Sprite.hpp"
#include "IDrawable.hpp"
#include "IRunnable.hpp"

Bullet::Bullet(const std::shared_ptr<const Sprite> sprite, const BulletOrbit &bulletOrbit, const D3DXVECTOR3 &position, const D3DXVECTOR3 &speed, const float radius, const float angle)
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

const bool Bullet::Enabled() const
{
	return enabled;
}

void Bullet::Enabled(const bool enabled)
{
	this->enabled = enabled;
}

const float Bullet::Radius() const
{
	return radius;
}

const D3DXVECTOR3 &Bullet::Position() const
{
	return position;
}

const float Bullet::Angle() const
{
	return angle;
}

void Bullet::Angle(const float angle)
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
