#include "File.h"

#include <fstream>
#include <sstream>

#include "DebugConsole.h"

using std::ifstream;
using std::stringstream;

string file::Read(string filename)
{
	stringstream text("");
	ifstream file;
	file.open(filename);

	if (file.is_open())
	{
		console::Print("File open successful!", console::GREEN);

		string line;
		while (getline(file, line))
		{
			text << line << "\n";
		}
	}
	else
	{
		console::Print("File open failed!", console::RED);
	}

	file.close();
	return text.str();
}