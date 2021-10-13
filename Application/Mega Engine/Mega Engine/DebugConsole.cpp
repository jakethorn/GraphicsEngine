#include "DebugConsole.h"

// includes

#include <fcntl.h>
#include <io.h>
#include <iostream>

// using

using std::ios;
using std::cout;
using std::count;

void console::Init()
{
	//Create a console for this application
	AllocConsole();

	//Redirect unbuffered STDOUT to the console
	HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int SystemOutput = _open_osfhandle(intptr_t(ConsoleOutput), _O_TEXT);
	FILE *COutputHandle = _fdopen(SystemOutput, "w");
	*stdout = *COutputHandle;
	setvbuf(stdout, NULL, _IONBF, 0);

	//Redirect unbuffered STDERR to the console 
	HANDLE ConsoleError = GetStdHandle(STD_ERROR_HANDLE);
	int SystemError = _open_osfhandle(intptr_t(ConsoleError), _O_TEXT);
	FILE *CErrorHandle = _fdopen(SystemError, "w");
	*stderr = *CErrorHandle;
	setvbuf(stderr, NULL, _IONBF, 0);

	//Redirect unbuffered STDIN to the console
	HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	int SystemInput = _open_osfhandle(intptr_t(ConsoleInput), _O_TEXT);
	FILE *CInputHandle = _fdopen(SystemInput, "r");
	*stdin = *CInputHandle;
	setvbuf(stdin, NULL, _IONBF, 0);

	//make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
	ios::sync_with_stdio(true);

	// jake
	gLineNumber = STARTING_LINE_NUMBER;
}

void console::Unin()
{
	//Write "Press any key to exit"
	HANDLE ConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD CharsWritten;
	WriteConsole(ConsoleOutput, "\nPress any key to exit", 22, &CharsWritten, 0);

	//Disable line-based input mode so we can get a single character
	HANDLE ConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(ConsoleInput, 0);

	//Read a single character
	TCHAR InputBuffer;
	DWORD CharsRead;
	ReadConsole(ConsoleInput, &InputBuffer, 1, &CharsRead, 0);
}

const int MIN_TABS{ 5 };
const int TAB_WIDTH{ 7 };

bool console::Print(bool OK, string name, int colour)
{
#if defined(DEBUG) || defined(_DEBUG)  

	if (DEBUG)
	{
		GotoXY(0, gLineNumber);
		SetRGB(colour);

		// 1
		cout << name;

		// 2
		int space = MIN_TABS - (name.length() / TAB_WIDTH);

		if (name.length() % 7 > 1)
		{
			space--;
		}

		// 3
		for (; space > 0; space--)
			cout << "\t";

		// 4
		cout << " - ";

		// 5
		if (OK)
		{
			SetRGB(2);
			cout << "OK";
		}
		else
		{
			SetRGB(1);
			cout << "Failed";
		}

		// a line was written
		gLineNumber++;
	}

#endif

	return OK;
}

bool console::Print(HRESULT hr, string name, int colour)
{
	return Print(!FAILED(hr), name, colour);
}

void console::Print(string message, int colour)
{
	GotoXY(0, gLineNumber);
	SetRGB(colour);

	message += '\n';

	cout << message;

	// a possible number of lines were written
	gLineNumber += count(message.begin(), message.end(), '\n');
}

void console::PrintAt(string message, int x, int y, int colour)
{
	GotoXY(x, y);
	SetRGB(colour);

	cout << message;
}

void console::ClearScreen()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);

	// jake
	gLineNumber = STARTING_LINE_NUMBER;
}

void console::GotoXY(int x, int y)
{
	COORD point;
	point.X = x; point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void console::SetRGB(int colour)
{
	switch (colour)
	{
	case WHITE:		// White on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	case RED:		// Red on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |	FOREGROUND_RED);
		break;
	case GREEN:		// Green on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |	FOREGROUND_GREEN);
		break;
	case YELLOW:	// Yellow on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |	FOREGROUND_RED | FOREGROUND_GREEN);
		break;
	case BLUE:		// Blue on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |	FOREGROUND_BLUE);
		break;
	case MAGENTA:	// Magenta on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |	FOREGROUND_RED | FOREGROUND_BLUE);
		break;
	case CYAN:		// Cyan on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |	FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	default:		// White on Black
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY |	FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		break;
	}
}

