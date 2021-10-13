// Mega

#pragma once

#ifndef CONSTANT_BUFFER_DATA_H
#define CONSTANT_BUFFER_DATA_H

#include "IConstantVariableData.h"

#include <map>
#include <string>

using ConstantBufferData = std::map<std::string, IConstantVariableData *>; 

// Constant Variable

// Constant Buffer

#endif /* CONSTANT_BUFFER_DATA_H */