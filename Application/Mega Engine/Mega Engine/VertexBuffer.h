// Mega

#pragma once

#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace vb
{
	void Init(vector<string> filenames);
	void Draw(string filename);
}

#endif