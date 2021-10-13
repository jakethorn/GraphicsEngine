// Mega

#pragma once

#ifndef COLOUR_H
#define COLOUR_H

#include <map>
#include <string>

using std::string;

namespace colour
{
	const float RED[]	{1.0f, 0.0f, 0.0f, 1.0f};
	const float GREEN[] {0.0f, 1.0f, 0.0f, 1.0f};
	const float BLUE[]	{0.0f, 0.0f, 1.0f, 1.0f};
	const float BLACK[]	{0.0f, 0.0f, 0.0f, 1.0f};
	const float WHITE[]	{1.0f, 1.0f, 1.0f, 1.0f};
	const float CLEAR[]	{0.0f, 0.0f, 0.0f, 0.0f};

	const string MAP_RED{ "red" };
	const string MAP_GREEN{ "green" };
	const string MAP_BLUE{ "blue" };
	const string MAP_BLACK{ "red" };
	const string MAP_WHITE{ "white" };
	const string MAP_CLEAR{ "clear" };

	const std::map<const string, const float * const> MAP
	{
		{ MAP_RED,		RED		},
		{ MAP_GREEN,	GREEN	},
		{ MAP_BLUE,		BLUE	},
		{ MAP_BLACK,	BLACK	},
		{ MAP_WHITE,	WHITE	},
		{ MAP_CLEAR,	CLEAR	}
	};
}

#endif