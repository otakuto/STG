#pragma once
#include "stdafx.h"
#include "DirectGraphics.h"
#include "DirectInput.h"
#include "BulletManager.h"
#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<const Sprite> sprite, const std::function<void(Enemy::Routine::caller_type&, Enemy&)> routine, const D3DXVECTOR3 &position, const float radius, const int life)
:
sprite(sprite),
routine(std::bind(routine, std::placeholders::_1, std::ref(*this))),
position(position),
radius(radius),
angle(0),
life(life),
enabled(true)
{
}

Enemy::~Enemy()
{
}

void Enemy::Draw() const
{
	sprite->Draw(position, angle);
}

void Enemy::Run()
{
	if (life)
	{
		routine();
	}
	else
	{
		enabled = false;
	}
}

const bool Enemy::Enabled() const
{
	return enabled;
}

void Enemy::Enabled(const bool enabled)
{
	this->enabled = enabled;
}

const int Enemy::Life() const
{
	return life;
}

void Enemy::Life(const int life)
{
	this->life = life;
}

D3DXVECTOR3 &Enemy::Position()
{
	return position;
}

void Enemy::Position(const D3DXVECTOR3 &position)
{
	this->position = position;
}

const float Enemy::Radius() const
{
	return radius;
}

void Enemy::Damage(const int damage)
{
	life -= damage;
	if (life < 0)
	{
		life = 0;
	}
}