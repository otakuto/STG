#pragma once
#include "stdafx.hpp"

class DirectInput
{
public:
	DirectInput(const HWND &hWnd);
	~DirectInput();

public:
	const std::vector<unsigned char> &Key() const;

public:
	void Run();

protected:
	static const int KEY_LENGTH;

protected:
	LPDIRECTINPUT8 directInput;
	LPDIRECTINPUTDEVICE8 keyboardDevice;
	LPDIRECTINPUTDEVICE8 mouseDevice;

	std::vector<unsigned char> key;
};
