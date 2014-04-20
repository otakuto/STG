#pragma once
#include "stdafx.hpp"
#include "DirectGraphics.hpp"
#include "Player.hpp"
#include "IDrawable.hpp"
#include "IRunnable.hpp"

class Game
{
public:
	static int const WINDOW_WIDTH;
	static int const WINDOW_HEIGHT;
	static int const OBJECT_ENABLED_WIDTH;
	static int const OBJECT_ENABLED_HEIGHT;
public:
	Game(HWND const &hWnd);
	~Game();

public:
	void Run();

protected:
	DirectGraphics directGraphics;
	DirectInput directInput;
	std::list<IRunnable*> iRunnableList;
	std::list<IDrawable*> iDrawableList;
};
