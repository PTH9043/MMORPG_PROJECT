#pragma once
#include "ACoreObject.h"

SPACE_BEGIN(Core)

class ASession : public ACoreObject {
public:



private:


	// ACoreObject��(��) ���� ��ӵ�
	EErrorState NativeConstruct(void* data = nullptr) override;

};

SPACE_END
