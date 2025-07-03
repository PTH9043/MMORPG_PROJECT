#pragma once
#include "ACoreObject.h"

SPACE_BEGIN(Core)

class ASession : public ACoreObject {
public:



private:


	// ACoreObject을(를) 통해 상속됨
	EErrorState NativeConstruct(void* data = nullptr) override;

};

SPACE_END
