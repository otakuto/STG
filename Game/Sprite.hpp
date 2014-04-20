#pragma once
#include "stdafx.hpp"

class Sprite
{
public:
	//@param range トリミング領域(画像左上基準)
	//@param center トリミング領域中心(トリミング矩形の左上基準)
	Sprite(LPDIRECT3DDEVICE9 const &direct3DDevice, LPCTSTR const &filename, RECT const &range, D3DXVECTOR3 const &center, bool const additive);
	~Sprite();

public:
	//描画。シーン中でないと例外をスロー
	//@param position	トリミング領域中心の位置 (スクリーン左上基準)
	void Draw(D3DXVECTOR3 const &position) const;

	//上のDrawに回転を付加
	//@param angle 回転角度 (回転中心はトリミング領域中心)
	void Draw(D3DXVECTOR3 const &position, float const angle) const;

	//上のDrawに回転、拡大縮小、透明度調整を付加
	//@param angle 回転角度(回転中心はトリミング領域中心)
	//@param scale 拡大率(拡大中心はトリミング中心)
	//@param alpha アルファ値
	void Draw(D3DXVECTOR3 const &position, float const angle, float const scale, int const alpha) const;

protected:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	LPDIRECT3DDEVICE9 const &direct3DDevice;
	RECT const range;
	D3DXVECTOR3 const center;
	bool additive;

protected:
	void setRenderState() const;
};
