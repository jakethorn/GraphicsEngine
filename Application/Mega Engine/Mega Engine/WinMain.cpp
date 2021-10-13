#include "WinMain.h"

#include <sstream>

#include "DebugConsole.h"
#include "Direct3D.h"
#include "Renderer.h"
#include "Timer.h"
#include "Window.h"

using std::stringstream;
using console::Print;

// static variables

Timer	*timer;
Window	*window;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	/*
	1. Console
	2. Window
	3. Direct3D
	4. Game
	5. Timer

	6. Message Loop
	*/

	console::Init();															// Console
	window	= new Window(hInstance, nCmdShow, WndProc, 1600, 900);				// Window
	d3d::Init(window->GetHandle(), window->GetWidth(), window->GetHeight());	// Direct3D
	renderer::Init();															// Renderer
	timer	= new Timer();														// Timer

	// Message Loop
	MSG msg{ 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			timer->Tick();

			renderer::Update(timer->DeltaTime());
			renderer::Render();
		}
	}

	delete timer;		// Timer
	renderer::Unin();	// Renderer
	d3d::Unin();		// Direct3D
	delete window;		// Window
	console::Unin();	// Console

	return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
		{
			timer->Stop();
		}
		else
		{
			timer->Start();
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_SIZE:
		window->SetDimensions(LOWORD(lParam), HIWORD(lParam));
		return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 160;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 90;
		return 0;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		renderer::OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		renderer::OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	case WM_MOUSEMOVE:
		renderer::OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;

	case WM_KEYDOWN:
		renderer::OnKeyDown(wParam);
		return 0;

	case WM_KEYUP:
		renderer::OnKeyUp(wParam);
		return 0;

	case WM_ENTERSIZEMOVE:
		timer->Stop();
		return 0;

	case WM_EXITSIZEMOVE:
		d3d::Resize(window->GetWidth(), window->GetHeight());

		timer->Start();
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

UINT GetWindowWidth()
{
	return window->GetWidth();
}

UINT GetWindowHeight()
{
	return window->GetHeight();
}