#pragma once
#include "ACoreBase.h"

SPACE_BEGIN(Core)

class ACoreManger abstract : public ACoreBase {
public:
	ACoreManger();
	virtual ~ACoreManger();

	DECLARE_GET_TYPENAME(ACoreManger)
	virtual EErrorState NativeConstruct(void* data = nullptr) = 0;
};

SPACE_END

