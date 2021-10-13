#include "InputLayout.h"

unsigned int inputlayout::CreateFromString( vector<string> elements )
{
	unsigned int bitset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		if		(elements[i] == "position")	bitset |= inputlayout::POSITION;
		else if (elements[i] == "normal")	bitset |= inputlayout::NORMAL;
	}

	return bitset;
}