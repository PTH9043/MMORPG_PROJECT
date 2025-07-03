#include "CoreDefines.h"
#include "ATaskQueue.h"

SPACE_BEGIN(Core)

ATaskQueue::ATaskQueue()
{
}

ATaskQueue::~ATaskQueue() { }

EErrorState ATaskQueue::NativeConstruct(void* data)
{
    return EErrorState::None;
}


SPACE_END