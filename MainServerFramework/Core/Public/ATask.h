#pragma once
#include "ACoreUnit.h"

SPACE_BEGIN(Core)
class AAsyncDispatcher;

enum class ETaskState { Pending, Running, Completed, Cancelled };
enum class EPriority { High, Normal, Low, Count }; // Count is a utility

using TASKFUNC = std::function<EErrorState(AAsyncDispatcher* asyncDispatcher)>;

class ATask : public ACoreUnit<ATask> {
public:
	ATask(TASKFUNC&& func, EPriority ePriority, AAsyncDispatcher* asyncDispatcher);
	ATask(TASKFUNC&& func, EPriority ePriority, int32 dataSize, byte* data);
	virtual ~ATask();

	DECLARE_GET_TYPENAME(ATask)
	virtual String ToContext() const override;

	virtual void Execute() = 0;

	ETaskState GetTaskState() const { return _eTaskState; }
	EPriority GetPriority() const { return _ePriority; }

	void SetPriority(EPriority priority) { CoreFunc::AtomicChangeValue(_ePriority, priority); }
protected:
	void RunFunc();

private:
	ETaskState					_eTaskState;
	EPriority						_ePriority;
	AAsyncDispatcher*	_AsyncDispatcher;
	TASKFUNC					_Func;
};


SPACE_END