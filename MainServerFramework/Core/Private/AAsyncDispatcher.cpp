#include "CoreDefines.h"
#include "AAsyncDispatcher.h"

SPACE_BEGIN(Core)

AAsyncDispatcher::AAsyncDispatcher(int32 dataSize, byte* data) : 
	 _DataSize{dataSize}
{
	_DataContainer.resize(_DataSize);
	::memcpy(&_DataContainer, data, dataSize);
}

AAsyncDispatcher::~AAsyncDispatcher()
{
}

String AAsyncDispatcher::ToContext() const
{
	return __super::ToContext();
}



SPACE_END