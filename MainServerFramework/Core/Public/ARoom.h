#pragma once
#include "ACoreObject.h"

SPACE_BEGIN(Core)
class ASession;


class ARoom : public ACoreObject {
public:
	// ACoreObject��(��) ���� ��ӵ�
	EErrorState NativeConstruct(void* data = nullptr) override;

private:
	Atomic_int32	_iRoomID;
};

SPACE_END
