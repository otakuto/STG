#pragma once
#include "stdafx.h"
#include "AnimationSprite.h"

AnimationSprite::AnimationSprite(const LPDIRECT3DDEVICE9 &direct3DDevice, const std::vector<const LPDIRECT3DTEXTURE9> &texture, const RECT &range, const D3DXVECTOR3 &center, const bool additive, const int interval)
:
direct3DDevice(direct3DDevice),
texture(texture),
range(range),
center(center),
additive(additive),
interval(interval),
count(0)
{
	D3DXCreateSprite(direct3DDevice, &sprite);
}

AnimationSprite::~AnimationSprite()
{
}

void AnimationSprite::Draw(const D3DXVECTOR3 &position) const
{
	/*
	D3DXVECTOR3 p = position;
	p.x = (int)p.x;
	p.y = (int)p.y;
	p.z = (int)p.z;
	*/
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	setRenderState();
	sprite->Draw(texture[count / interval], &range, &center, &position, D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF));
	sprite->End();
}

void AnimationSprite::Draw(const D3DXVECTOR3 &position, const float angle) const
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX matRotation;
	D3DXMatrixRotationZ(&matRotation, angle);
	D3DXMATRIX matTranslation;
	D3DXMatrixTranslation(&matTranslation, position.x, position.y, 0);
	D3DXMATRIX matWorld;
	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	matWorld = matRotation*matTranslation;
	sprite->SetTransform(&matWorld);
	setRenderState();
	sprite->Draw(texture[count / interval], &range, &center, 0, D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF));
	sprite->SetTransform(&matIdentity);
	sprite->End();
}

void AnimationSprite::Draw(const D3DXVECTOR3 &position, const float angle, const float scale, const int alpha) const
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX matScale, matRotation, matTranslation, matWorld, matIdentity;
	D3DXMatrixScaling(&matScale, scale, scale, scale);
	D3DXMatrixRotationZ(&matRotation, angle);
	D3DXMatrixTranslation(&matTranslation, position.x, position.y, 0);
	D3DXMatrixIdentity(&matIdentity);
	matWorld = matScale * matRotation * matTranslation;
	sprite->SetTransform(&matWorld);
	setRenderState();
	if (additive)
	{
		sprite->Draw(texture[count / interval], &range, &center, 0, D3DCOLOR_ARGB(alpha, alpha, alpha, alpha));
	}
	else
	{
		sprite->Draw(texture[count / interval], &range, &center, 0, D3DCOLOR_ARGB(alpha, 0xFF, 0xFF, 0xFF));
	}
	sprite->SetTransform(&matIdentity);
	sprite->End();
}

void AnimationSprite::CountUp()
{
	++count;
}

void AnimationSprite::setRenderState() const
{
	DWORD src, dest;
	if (additive)
	{
		src = D3DBLEND_ONE;
		dest = D3DBLEND_ONE;
	}
	else
	{
		src = D3DBLEND_SRCALPHA;
		dest = D3DBLEND_INVSRCALPHA;
	}
	direct3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	direct3DDevice->SetRenderState(D3DRS_SRCBLEND, src);
	direct3DDevice->SetRenderState(D3DRS_DESTBLEND, dest);
}
