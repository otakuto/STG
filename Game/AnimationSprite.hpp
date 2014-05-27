#pragma once
#include "stdafx.hpp"

class AnimationSprite
{
public:
	AnimationSprite(LPDIRECT3DDEVICE9 const & direct3DDevice, std::vector<LPDIRECT3DTEXTURE9 const> const & texture, RECT const & range, D3DXVECTOR3 const & center, bool constadditive, int const interval);
	~AnimationSprite();

public:
	void Draw(D3DXVECTOR3 const & position) const;
	void Draw(D3DXVECTOR3 const & position, float const angle) const;
	void Draw(D3DXVECTOR3 const & position, float const angle, float const scale, int const alpha) const;
	void CountUp();

protected:
	void setRenderState() const;

protected:
	LPDIRECT3DDEVICE9 const & direct3DDevice;
	LPD3DXSPRITE sprite;
	std::vector<LPDIRECT3DTEXTURE9 const> const & texture;
	RECT const & range;
	D3DXVECTOR3 const & center;
	bool additive;
	int interval;
	int count;
};

