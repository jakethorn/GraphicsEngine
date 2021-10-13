// Mega

#pragma once

#ifndef COMMON_H
#define COMMON_H

#define ReleaseCOM(x) { if (x) { x->Release(); x = nullptr; } }
#define SafeDelete(x) { if (x) { delete x;     x = nullptr; } }

#endif