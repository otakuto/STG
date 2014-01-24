#pragma once
#include "stdafx.hpp"
#include "DirectInput.hpp"

const int DirectInput::KEY_LENGTH = 256;

DirectInput::DirectInput(const HWND &hWnd)
:
key(std::vector<unsigned char>(KEY_LENGTH))
{
	DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(&directInput), nullptr);

	directInput->CreateDevice(GUID_SysKeyboard, &keyboardDevice, nullptr);
	keyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	keyboardDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));
	keyboardDevice->Acquire();

	directInput->CreateDevice(GUID_SysMouse, &mouseDevice, nullptr);
	mouseDevice->SetDataFormat(&c_dfDIMouse);
	mouseDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY));
	{
		DIPROPDWORD dipdw;
		dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = 16;
		mouseDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	}
	mouseDevice->Acquire();
}

DirectInput::~DirectInput()
{
	SAFE_RELEASE(directInput);
	keyboardDevice->Unacquire();
	SAFE_RELEASE(keyboardDevice);
}

const std::vector<unsigned char> &DirectInput::Key() const
{
	return key;
}

void DirectInput::Run()
{
	if (FAILED(keyboardDevice->GetDeviceState((sizeof(unsigned char)* KEY_LENGTH), key.data())))
	{
		keyboardDevice->Acquire();
	}
}