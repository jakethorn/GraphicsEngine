//Mega

#pragma once

#ifndef INPUT_LAYOUT_H
#define INPUT_LAYOUT_H

#include <d3d11.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace inputlayout
{
	const UINT NUM_STD_ELEMENTS = 2;

	const D3D11_INPUT_ELEMENT_DESC POSITION_ELEMENT = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, -1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	const D3D11_INPUT_ELEMENT_DESC NORMAL_ELEMENT	= { "NORMAL",	0, DXGI_FORMAT_R32G32B32_FLOAT, -1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };

	const D3D11_INPUT_ELEMENT_DESC STD_ELEMENT[] { POSITION_ELEMENT, NORMAL_ELEMENT };

	const UINT POSITION	= 1;
	const UINT NORMAL	= 2;

	const D3D11_INPUT_ELEMENT_DESC NULL_ELEMENT = { "", -1, DXGI_FORMAT_UNKNOWN, -1, -1, D3D11_INPUT_PER_VERTEX_DATA, -1 };

	unsigned int CreateFromString( vector<string> elements );
}

#endif