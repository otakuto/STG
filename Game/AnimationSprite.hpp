#pragma once
#include "stdafx.hpp"

class AnimationSprite
{
public:
	AnimationSprite(const LPDIRECT3DDEVICE9 &direct3DDevice, const std::vector<const LPDIRECT3DTEXTURE9> &texture, const RECT &range, const D3DXVECTOR3 &center, const bool additive, const int interval);
	~AnimationSprite();

public:
	void Draw(const D3DXVECTOR3 &position) const;
	void Draw(const D3DXVECTOR3 &position, const float angle) const;
	void Draw(const D3DXVECTOR3 &position, const float angle, const float scale, const int alpha) const;
	void CountUp();

protected:
	void setRenderState() const;

protected:
	const LPDIRECT3DDEVICE9 &direct3DDevice;
	LPD3DXSPRITE sprite;
	const std::vector<const LPDIRECT3DTEXTURE9> &texture;
	const RECT &range;
	const D3DXVECTOR3 &center;
	bool additive;
	int interval;
	int count;
};

