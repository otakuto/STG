#pragma once
#include "stdafx.h"

class Sprite
{
public:
	//@param range トリミング領域(画像左上基準)
	//@param center トリミング領域中心(トリミング矩形の左上基準)
	Sprite(const LPDIRECT3DDEVICE9 &direct3DDevice, const LPCTSTR &filename, const RECT &range, const D3DXVECTOR3 &center, const bool additive);
	~Sprite();

public:
	//描画。シーン中でないと例外をスロー
	//@param position	トリミング領域中心の位置 (スクリーン左上基準)
	void Draw(const D3DXVECTOR3 &position) const;

	//上のDrawに回転を付加
	//@param angle 回転角度 (回転中心はトリミング領域中心)
	void Draw(const D3DXVECTOR3 &position, const float angle) const;

	//上のDrawに回転、拡大縮小、透明度調整を付加
	//@param angle 回転角度(回転中心はトリミング領域中心)
	//@param scale 拡大率(拡大中心はトリミング中心)
	//@param alpha アルファ値
	void Draw(const D3DXVECTOR3 &position, const float angle, const float scale, const int alpha) const;

protected:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	const LPDIRECT3DDEVICE9 &direct3DDevice;
	const RECT range;
	const D3DXVECTOR3 center;
	bool additive;

protected:
	void setRenderState() const;
};
