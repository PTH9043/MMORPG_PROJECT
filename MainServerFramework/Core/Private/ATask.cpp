#include "CoreDefines.h"
#include "ATask.h"
#include "AAsyncDispatcher.h"

SPACE_BEGIN(Core)

ATask::ATask(TASKFUNC&& func, EPriority ePriority, AAsyncDispatcher* asyncDispatcher) :
	_Func{ func }, _eTaskState{ ETaskState::Pending }, _ePriority{ ePriority }, _AsyncDispatcher{ asyncDispatcher }
{
}

ATask::ATask(TASKFUNC&& func, EPriority ePriority, int32 dataSize, byte* data) :
	_Func{func}, _eTaskState{ ETaskState::Pending }, _ePriority{ ePriority }, _AsyncDispatcher{ nullptr }
{
	_AsyncDispatcher = AAsyncDispatcher::Create(dataSize, data);
}

ATask::~ATask()
{
	mdelete(_AsyncDispatcher);
}

String ATask::ToContext() const
{
	return __super::ToContext();
}

void ATask::RunFunc()
{
	CoreFunc::AtomicChangeValue(_eTaskState, ETaskState::Running);
	try
	{
		_Func(_AsyncDispatcher);
	}
	catch (std::exception ex) 
	{
		CoreFunc::AtomicChangeValue(_eTaskState, ETaskState::Cancelled);
	}
	CoreFunc::AtomicChangeValue(_eTaskState, ETaskState::Completed);
}

SPACE_END
