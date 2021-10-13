// Mega

#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

class Window
{
public:
	Window(HINSTANCE hInstance, int nCmdShow, WNDPROC wndProc, UINT width, UINT height);

	const HWND & GetHandle() { return mHWnd; }

	UINT GetWidth() { return mWidth; }
	UINT GetHeight() { return mHeight; }
	void SetDimensions(UINT width, UINT height);

	const static UINT XOffset = 200;
	const static UINT YOffset = 50;

private:
	HWND mHWnd;
	UINT mWidth;
	UINT mHeight;
};

#endif