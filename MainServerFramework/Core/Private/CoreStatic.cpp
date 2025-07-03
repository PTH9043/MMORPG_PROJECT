#include "CoreDefines.h"
#include "CoreStatic.h"

namespace Core
{
	thread_local int32 CoreStatic::ThreadID_RW = 0;
}