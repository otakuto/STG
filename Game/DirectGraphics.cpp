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
		//ウィンドウハンドル確認
		throw TEXT("Direct3Dの作成に失敗しました\nウィンドウハンドルがありません");
	}
	if (!(direct3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		//Direct3Dオブジェクトの作成
		throw TEXT("Direct3Dの作成に失敗しました");
	}

	D3DCAPS9 caps;
	//ダブルステンシルのサポートを確認
	direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (!(caps.StencilCaps & D3DSTENCILCAPS_TWOSIDED))
	{
		MessageBox(0, TEXT("ダブルステンシルに対応していません"), TEXT(""), MB_OK);
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
	//Zバッファ24ビット、ステンシルバッファ8ビットなのでOK
	parameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	//ダブルステンシル
	parameters.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	if (FAILED(direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &parameters, &device)))
	{
		if (FAILED(direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters, &device)))
		{
			MessageBox(0, TEXT("HALモードでDIRECT3Dデバイスを作成できません\nREFモードで再試行します"), nullptr, MB_OK);
			if (FAILED(direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &parameters, &device)))
			{
				if (FAILED(direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &parameters, &device)))
				{
					throw TEXT("DIRECT3Dデバイスの作成に失敗しました");
				}
			}
		}
	}
}

void DirectGraphics::setRenderingConfiguration()
{
	//Zバッファー処理を有効にする
	device->SetRenderState(D3DRS_ZENABLE, true);
	//カリングする
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//ライトを有効にする
	device->SetRenderState(D3DRS_LIGHTING, true);
	//アンビエントライト(環境光)を設定する
	device->SetRenderState(D3DRS_AMBIENT, 0x00000000);
	//スペキュラ(鏡面反射)を有効にする
	device->SetRenderState(D3DRS_SPECULARENABLE, true);
}

void DirectGraphics::setFogConfiguration()
{
	D3DCAPS9 caps;
	ZeroMemory(&caps, sizeof(D3DCAPS9));
	device->GetDeviceCaps(&caps);
	if ((caps.RasterCaps & D3DPRASTERCAPS_FOGTABLE) == 0)
	{
		if (MessageBox(0, TEXT("ピクセルフォグが使えない可能性があります。続行しますか?"), TEXT("質問"), MB_ABORTRETRYIGNORE) == IDABORT)
		{
			throw TEXT("フォグ設定に失敗しました");
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

