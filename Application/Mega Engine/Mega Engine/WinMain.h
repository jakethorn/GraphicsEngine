// Mega

#pragma once

#ifndef WIN_MAIN_H
#define WIN_MAIN_H

#include <windows.h>
#include <windowsx.h>

int		WINAPI		WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);	
LRESULT	CALLBACK	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

UINT GetWindowWidth();
UINT GetWindowHeight();

#endif