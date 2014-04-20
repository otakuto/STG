#pragma once
#include "stdafx.hpp"
#include "Sprite.hpp"

Sprite::Sprite(LPDIRECT3DDEVICE9 const &direct3DDevice, const LPCTSTR &filename, RECT const &range, D3DXVECTOR3 const&center, const bool additive)
:
direct3DDevice(direct3DDevice),
range(range),
center(center),
additive(additive)
{
	D3DXCreateSprite(direct3DDevice, &sprite);
	if (D3DXCreateTextureFromFileEx(
		direct3DDevice,
		filename,
		0,
		0,
		0,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		&texture) != D3D_OK)
	{
		throw TEXT("テクスチャの作成に失敗しました");
	}
}

Sprite::~Sprite()
{
	SAFE_RELEASE(sprite);
	SAFE_RELEASE(texture);
}

void Sprite::setRenderState() const
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

void Sprite::Draw(D3DXVECTOR3 const&position) const
{
	/*
	position.x = (int)position.x;
	position.y = (int)position.y;
	position.z = (int)position.z;
	*/
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	setRenderState();
	sprite->Draw(texture, &range, &center, &position, D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF));
	sprite->End();
}

void Sprite::Draw(D3DXVECTOR3 const&position, float const angle) const
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
	sprite->Draw(texture, &range, &center, 0, D3DCOLOR_ARGB(0xFF, 0xFF, 0xFF, 0xFF));
	sprite->SetTransform(&matIdentity);
	sprite->End();
}

void Sprite::Draw(D3DXVECTOR3 const&position, float const angle, float const scale, int const alpha) const
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
		sprite->Draw(texture, &range, &center, 0, D3DCOLOR_ARGB(alpha, alpha, alpha, alpha));
	}
	else
	{
		sprite->Draw(texture, &range, &center, 0, D3DCOLOR_ARGB(alpha, 0xFF, 0xFF, 0xFF));
	}
	sprite->SetTransform(&matIdentity);
	sprite->End();
}