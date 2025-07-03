#pragma once
#include "ACoreManger.h"
#include "ATask.h"

SPACE_BEGIN(Core)

class ATaskQueue : public ACoreManger {
public:
	ATaskQueue();
	virtual ~ATaskQueue();
	DECLARE_GET_TYPENAME(ATaskQueue)

	virtual EErrorState NativeConstruct(void* data = nullptr) override;

private:

};

SPACE_END