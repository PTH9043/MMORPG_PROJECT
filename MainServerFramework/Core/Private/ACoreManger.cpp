#include "CoreDefines.h"
#include "ACoreManger.h"

SPACE_BEGIN(Core)

ACoreManger::ACoreManger() :
	ACoreBase(EBaseType::Manger, IDGenerator::GenManger())
{
}

ACoreManger::~ACoreManger()
{
}


SPACE_END

