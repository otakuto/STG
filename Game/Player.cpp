#pragma once
#include "stdafx.hpp"
#include "Player.hpp"
#include "DirectGraphics.hpp"
#include "DirectInput.hpp"
#include "BulletManager.hpp"
#include "Sprite.hpp"
#include "Game.hpp"

Player::Player(const DirectGraphics &directGraphics, const std::vector<unsigned char> &key, BulletManager &bulletManager)
:
sprite(directGraphics.Device(), TEXT("Resource/Player.png"), RECT{0, 0, 16, 16}, D3DXVECTOR3(7, 7, 0), false),
spriteBullet(std::make_shared<Sprite>(directGraphics.Device(), TEXT("Resource/Shot.png"), RECT{0, 0, 8, 8}, D3DXVECTOR3(3, 3, 0), false)),
key(key),
position(static_cast<float>(Game::OBJECT_ENABLED_WIDTH / 2), static_cast<float>(500), 0),
bulletManager(bulletManager),
radius(static_cast<float>(8)),
shotTime(0),
invincibleTime(0)
{
}

Player::~Player()
{
}

int const Player::Life() const
{
	return life;
}

void Player::Life(int const life)
{
	if (invincibleTime)
	{
	}
	else
	{
		this->life = life;
	}
}

D3DXVECTOR3 &Player::Position()
{
	return position;
}

void Player::Position(D3DXVECTOR3 const &position)
{
	this->position = position;
}

float const Player::Radius() const
{
	return radius;
}

void Player::Draw() const
{
	if ((invincibleTime % 2) == 0)
	{
		sprite.Draw(position);
	}
}

void Player::Run()
{
	static int const INVINCIBLE_TIME = 120;
	if (invincibleTime)
	{
		--invincibleTime;
	}
	else if (!life)
	{
		position = D3DXVECTOR3(static_cast<float>(Game::OBJECT_ENABLED_WIDTH / 2), static_cast<float>(500), 0);
		life = 1;
		invincibleTime = INVINCIBLE_TIME;
	}

	D3DXVECTOR3 move = D3DXVECTOR3(0, 0, 0);
	if (key[DIK_UP])
	{
		--move.y;
	}
	if (key[DIK_DOWN])
	{
		++move.y;
	}
	if (key[DIK_RIGHT])
	{
		++move.x;
	}
	if (key[DIK_LEFT])
	{
		--move.x;
	}
	static float const NORMAL_SPEED = 4;
	static float const LOW_SPEED = 2;
	D3DXVECTOR3 nextPosition = D3DXVECTOR3(0, 0, 0);
	if (key[DIK_LSHIFT])
	{
		nextPosition = position + (LOW_SPEED * move);
	}
	else
	{
		nextPosition = position + (NORMAL_SPEED * move);
	}
	static float const MARGIN = 8;
	if (!(MARGIN <= nextPosition.x))
	{
		position.x = MARGIN;
	}
	else if (!(nextPosition.x < (Game::OBJECT_ENABLED_WIDTH - MARGIN)))
	{
		position.x = Game::OBJECT_ENABLED_WIDTH - MARGIN - 1;
	}
	else
	{
		position.x = nextPosition.x;
	}
	if (!(MARGIN <= nextPosition.y))
	{
		position.y = MARGIN;
	}
	else if (!(nextPosition.y < (Game::OBJECT_ENABLED_HEIGHT - MARGIN)))
	{
		position.y = Game::OBJECT_ENABLED_HEIGHT - MARGIN - 1;
	}
	else
	{
		position.y = nextPosition.y;
	}

	static int const SHOT_TIME_INTERVAL = 4;
	if (shotTime)
	{
		--shotTime;
	}
	else
	{
		if (key[DIK_Z])
		{
			static const Bullet::BulletOrbit BULLET_ORBIT = [](D3DXVECTOR3 &position, D3DXVECTOR3 &speed, const unsigned long long &time)
			{
				position += speed;
			};
			static D3DXVECTOR3 const SHOT_POSITION_RIGHT = D3DXVECTOR3(12, -4, 0);
			static D3DXVECTOR3 const SHOT_POSITION_LEFT = D3DXVECTOR3(-12, -4, 0);
			static D3DXVECTOR3 const SPEED = D3DXVECTOR3(0, -10, 0);
			bulletManager.BulletList().push_back(new Bullet(spriteBullet, BULLET_ORBIT, position + SHOT_POSITION_RIGHT, SPEED, 4, 0));
			bulletManager.BulletList().push_back(new Bullet(spriteBullet, BULLET_ORBIT, position + SHOT_POSITION_LEFT, SPEED, 4, 0));
			shotTime = SHOT_TIME_INTERVAL;
		}
	}
}
