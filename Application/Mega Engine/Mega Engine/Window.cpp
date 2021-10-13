#include "Window.h"

#include "DebugConsole.h"

Window::Window(HINSTANCE hInstance, int nCmdShow, WNDPROC wndProc, UINT width, UINT height)
{
	mWidth = width;
	mHeight = height;

	// REGISTER CLASS

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	wc.lpszClassName = L"WindowClass1";

	ATOM retval = RegisterClassEx(&wc);

	console::Print(static_cast<bool>(retval), "RegisterClassEx");

	// CREATE WINDOW

	// get real window rectangle 
	RECT R = { 0, 0, mWidth, mHeight };
	AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int newWidth = R.right - R.left;
	int newHeight = R.bottom - R.top;

	mHWnd = CreateWindowEx(
		NULL,
		wc.lpszClassName,
		L"Mega Engine",
		WS_OVERLAPPEDWINDOW,
		XOffset,
		YOffset,
		newWidth,
		newHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	console::Print(mHWnd, "CreateWindowEx");

	// SHOW WINDOW

	ShowWindow(mHWnd, nCmdShow);
	UpdateWindow(mHWnd);
}

void Window::SetDimensions(UINT width, UINT height)
{
	mWidth = width;
	mHeight = height;
}