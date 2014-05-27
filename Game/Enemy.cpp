#pragma once
#include "stdafx.hpp"
#include "DirectGraphics.hpp"
#include "DirectInput.hpp"
#include "BulletManager.hpp"
#include "Enemy.hpp"

Enemy::Enemy(std::shared_ptr<Sprite const> sprite, const std::function<void(Enemy::Routine::caller_type&, Enemy&)> routine, const D3DXVECTOR3 &position, float const radius, int const life)
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

bool const Enemy::Enabled() const
{
	return enabled;
}

void Enemy::Enabled(bool const enabled)
{
	this->enabled = enabled;
}

int const Enemy::Life() const
{
	return life;
}

void Enemy::Life(int const life)
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

float const Enemy::Radius() const
{
	return radius;
}

void Enemy::Damage(int const damage)
{
	life -= damage;
	if (life < 0)
	{
		life = 0;
	}
}