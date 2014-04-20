#pragma once
#include "stdafx.hpp"

class Sprite
{
public:
	//@param range �g���~���O�̈�(�摜����)
	//@param center �g���~���O�̈撆�S(�g���~���O��`�̍���)
	Sprite(LPDIRECT3DDEVICE9 const &direct3DDevice, LPCTSTR const &filename, RECT const &range, D3DXVECTOR3 const &center, bool const additive);
	~Sprite();

public:
	//�`��B�V�[�����łȂ��Ɨ�O���X���[
	//@param position	�g���~���O�̈撆�S�̈ʒu (�X�N���[������)
	void Draw(D3DXVECTOR3 const &position) const;

	//���Draw�ɉ�]��t��
	//@param angle ��]�p�x (��]���S�̓g���~���O�̈撆�S)
	void Draw(D3DXVECTOR3 const &position, float const angle) const;

	//���Draw�ɉ�]�A�g��k���A�����x������t��
	//@param angle ��]�p�x(��]���S�̓g���~���O�̈撆�S)
	//@param scale �g�嗦(�g�咆�S�̓g���~���O���S)
	//@param alpha �A���t�@�l
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
