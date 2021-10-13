// Mega

#pragma once

#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

#include <map>
#include <string>

struct ConstantVariable
{
	unsigned int offset;
	unsigned int length;
	unsigned int bufferSlot;
};

using ConstantBuffer = std::map<std::string, ConstantVariable>; 

// Constant Variable

// Constant Buffer

#endif /* CONSTANT_BUFFER_H */