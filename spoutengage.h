#ifndef SPOUTENGAGE_H
#define SPOUTENGAGE_H

#include "../M3/src/misc.h"

class IEventManager;
class IDataBus;

extern "C" __declspec(dllexport)
IGenPlugin* create(IEventManager* events, IDataBus* dbus);

extern "C" __declspec(dllexport)
void destroy(IGenPlugin* plugin);

#endif // SPOUTENGAGE_H
