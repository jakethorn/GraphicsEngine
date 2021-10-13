// Mega

#pragma once

#ifndef UNSTRUCTURED_FUNCTIONS_H
#define UNSTRUCTURED_FUNCTIONS_H

#include <d3d11.h>
#include <sstream>
#include <string>

using std::stringstream;
using std::showpos;

void *GetBufferData(ID3D11Device * const device, ID3D11Buffer *buffer, UINT byteWidth);

template<typename T>
void Print2DBuffer(T *buffer, UINT numColumns, UINT numRows)
{
	UINT n = numColumns * numRows;

	stringstream ss;
	for (int i = 0; i < n; ++i) {
		if (i % numColumns == 0 && i != 0) ss << "\n";
		ss << showpos << buffer[i] << " ";
	}

	Print(ss.str(), console::MAGENTA);
}

namespace help
{
	std::wstring ToWString( std::string text );
}

#endif