#include "CoreDefines.h"
#include "IDGenerator.h"

SPACE_BEGIN(Core)

Atomic_int64 IDGenerator::_ComponentIDGen{ 0 };
Atomic_int64 IDGenerator::_ObjectIDGen{ 0 };
Atomic_int64 IDGenerator::_ManagerIDGen{ 0 };

SPACE_END
