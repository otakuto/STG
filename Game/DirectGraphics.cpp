#pragma once
#include "stdafx.h"
#include "DirectGraphics.h"

DirectGraphics::DirectGraphics(const HWND &hWnd)
:
fogStart(150),
fogEnd(1000)
{
	if (!hWnd)
	{
		//�E�B���h�E�n���h���m�F
		throw TEXT("Direct3D�̍쐬�Ɏ��s���܂���\n�E�B���h�E�n���h��������܂���");
	}
	if (!(direct3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		//Direct3D�I�u�W�F�N�g�̍쐬
		throw TEXT("Direct3D�̍쐬�Ɏ��s���܂���");
	}

	D3DCAPS9 caps;
	//�_�u���X�e���V���̃T�|�[�g���m�F
	direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (!(caps.StencilCaps & D3DSTENCILCAPS_TWOSIDED))
	{
		MessageBox(0, TEXT("�_�u���X�e���V���ɑΉ����Ă��܂���"), TEXT(""), MB_OK);
	}
	createDirect3DDeviceObject(hWnd);
	setRenderingConfiguration();
	setFogConfiguration();
}

DirectGraphics::~DirectGraphics()
{
	SAFE_RELEASE(direct3D);
	SAFE_RELEASE(device);
}

void DirectGraphics::createDirect3DDeviceObject(const HWND &hWnd)
{
	D3DPRESENT_PARAMETERS parameters;
	ZeroMemory(&parameters, sizeof(D3DPRESENT_PARAMETERS));
	parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	parameters.BackBufferFormat = D3DFMT_UNKNOWN;
	parameters.BackBufferCount = 1;
	parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	parameters.Windowed = true;
	parameters.EnableAutoDepthStencil = true;
	//Z�o�b�t�@24�r�b�g�A�X�e���V���o�b�t�@8�r�b�g�Ȃ̂�OK
	parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	//�_�u���X�e���V��
	parameters.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	if (FAILED(direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &parameters, &device)))
	{
		if (FAILED(direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters, &device)))
		{
			MessageBox(0, TEXT("HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�"), nullptr, MB_OK);
			if (FAILED(direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &parameters, &device)))
			{
				if (FAILED(direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters, &device)))
				{
					throw TEXT("DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���");
				}
			}
		}
	}
}

void DirectGraphics::setRenderingConfiguration()
{
	//Z�o�b�t�@�[������L���ɂ���
	device->SetRenderState(D3DRS_ZENABLE, true);
	//�J�����O����
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//���C�g��L���ɂ���
	device->SetRenderState(D3DRS_LIGHTING, true);
	//�A���r�G���g���C�g(����)��ݒ肷��
	device->SetRenderState(D3DRS_AMBIENT, 0x00000000);
	//�X�y�L����(���ʔ���)��L���ɂ���
	device->SetRenderState(D3DRS_SPECULARENABLE, true);
}

void DirectGraphics::setFogConfiguration()
{
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));
	device->GetDeviceCaps(&caps);
	if ((caps.RasterCaps & D3DPRASTERCAPS_FOGTABLE) == 0)
	{
		if (MessageBox(0, TEXT("�s�N�Z���t�H�O���g���Ȃ��\��������܂��B���s���܂���?"), TEXT("����"), MB_ABORTRETRYIGNORE) == IDABORT)
		{
			throw TEXT("�t�H�O�ݒ�Ɏ��s���܂���");
		}
	}
	device->SetRenderState(D3DRS_FOGENABLE, true);
	device->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(150, 255, 255, 255));
	device->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);
	device->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);
	device->SetRenderState(D3DRS_FOGSTART, static_cast<DWORD>(fogStart));
	device->SetRenderState(D3DRS_FOGEND, static_cast<DWORD>(fogEnd));
}


const LPDIRECT3DDEVICE9 &DirectGraphics::Device() const
{
	return device;
}

