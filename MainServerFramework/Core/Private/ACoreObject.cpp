#include "CoreDefines.h"
#include "ACoreObject.h"


SPACE_BEGIN(Core)


ACoreObject::ACoreObject() :
	ACoreBase(EBaseType::Object, IDGenerator::GenObjectID())
{
}

ACoreObject::~ACoreObject()
{
}

void ACoreObject::InitializeGlobalData()
{

}

String ACoreObject::ToContext() const
{
	return __super::ToContext() + ", Destroy=" + Core::ToString(IsDestory());
}

SPACE_END