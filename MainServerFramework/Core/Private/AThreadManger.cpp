#include "CoreDefines.h"
#include "AThreadManger.h"

SPACE_BEGIN(Core)

AThreadManger::AThreadManger()
	: _Threads{}, _ThreadNums{0}
{
}

AThreadManger::~AThreadManger()
{
	_Threads.clear();
	_ThreadNames.clear();
	_ThreadIndexes.clear();
}

EErrorState AThreadManger::NativeConstruct(void* data)
{
	return EErrorState::None;
}

void AThreadManger::RegisterFunc(const THREADFUNC& callBack, void* data, const String& name)
{
	int32 currentThreadID = _ThreadNums++;
	_ThreadNames[currentThreadID] = name;
	_Threads.emplace_back(ThreadJoin, callBack, data, currentThreadID);
}

void AThreadManger::Join()
{
	for (THREAD& t : _Threads) {
		if (t.joinable()) {
			t.join();
		}
	}
	_Threads.clear();
}

void AThreadManger::ThreadJoin(const THREADFUNC& callBack, void* data, int32 currentThreadID)
{
	CoreStatic::ThreadID_RW = currentThreadID;
	try {
		callBack(data);
	}
	catch (const std::exception& ex) {
		OUTSYSTEMERRORMSG(ex);
	}
}


SPACE_END