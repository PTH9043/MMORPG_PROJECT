#include "CoreDefines.h"
#include "ACoreBase.h"

SPACE_BEGIN(Core)

ACoreBase::ACoreBase(EBaseType BaseType, int64 CoreID) :
	_eBaseType{ BaseType },  _iCoreID{ CoreID }
{
}

ACoreBase::~ACoreBase()
{
}

EErrorState ACoreBase::NativeConstruct(void* data)
{
	// 로그 작성하기
	return EErrorState();
}

String ACoreBase::ToContext() const
{
	return String("[") + GetTypeName()
		+ "] ID=" + Core::ToString(_iCoreID.load())
		+ ", Type=" + Core::ToString(static_cast<int>(_eBaseType));
}

SPACE_END