#ifndef SPOUTENGAGE_H
#define SPOUTENGAGE_H

#include "../M3/src/misc.h"

extern "C" __declspec(dllexport)
IGenPlugin* create();

extern "C" __declspec(dllexport)
void destroy(IGenPlugin* plugin);

#endif // SPOUTENGAGE_H
