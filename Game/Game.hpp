#pragma once
#include "stdafx.hpp"
#include "DirectGraphics.hpp"
#include "Player.hpp"
#include "IDrawable.hpp"
#include "IRunnable.hpp"

class Game
{
public:
	static const int WINDOW_WIDTH;
	static const int WINDOW_HEIGHT;
	static const int OBJECT_ENABLED_WIDTH;
	static const int OBJECT_ENABLED_HEIGHT;
public:
	Game(const HWND &hWnd);
	~Game();

public:
	void Run();

protected:
	DirectGraphics directGraphics;
	DirectInput directInput;
	std::list<IRunnable*> iRunnableList;
	std::list<IDrawable*> iDrawableList;
};
