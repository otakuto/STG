#pragma once
#include "stdafx.h"

class Sprite
{
public:
	//@param range �g���~���O�̈�(�摜����)
	//@param center �g���~���O�̈撆�S(�g���~���O��`�̍���)
	Sprite(const LPDIRECT3DDEVICE9 &direct3DDevice, const LPCTSTR &filename, const RECT &range, const D3DXVECTOR3 &center, const bool additive);
	~Sprite();

public:
	//�`��B�V�[�����łȂ��Ɨ�O���X���[
	//@param position	�g���~���O�̈撆�S�̈ʒu (�X�N���[������)
	void Draw(const D3DXVECTOR3 &position) const;

	//���Draw�ɉ�]��t��
	//@param angle ��]�p�x (��]���S�̓g���~���O�̈撆�S)
	void Draw(const D3DXVECTOR3 &position, const float angle) const;

	//���Draw�ɉ�]�A�g��k���A�����x������t��
	//@param angle ��]�p�x(��]���S�̓g���~���O�̈撆�S)
	//@param scale �g�嗦(�g�咆�S�̓g���~���O���S)
	//@param alpha �A���t�@�l
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
