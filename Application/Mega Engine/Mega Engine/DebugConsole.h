// Extrarius

#pragma once

#ifndef DEBUG_CONSOLE_H
#define DEBUG_CONSOLE_H

#include <windows.h>
#include <string>

using std::string;

namespace console
{
	// immutable values

	const bool DEBUG{ true };
	const UINT STARTING_LINE_NUMBER{ 3 };

	const int WHITE{ 0 };
	const int RED{ 1 };
	const int GREEN{ 2 };
	const int YELLOW{ 3 };
	const int BLUE{ 4 };
	const int MAGENTA{ 5 };
	const int CYAN{ 6 };

	// functions

	void Init();
	void Unin();

	bool Print(bool OK,		string name, int colour = WHITE);
	bool Print(HRESULT hr,	string name, int colour = WHITE);
	void Print(string message, int colour = WHITE);
	void PrintAt(string message, int x, int y, int colour = WHITE);

	void ClearScreen();
	void GotoXY(int x, int y);
	void SetRGB(int colour);

	// private variables

	static UINT gLineNumber;
}

#endif