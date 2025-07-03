#pragma once
#include "ACoreBase.h"

SPACE_BEGIN(Core)

class AThreadManger;

class ACoreObject abstract : public ACoreBase {
public:
	ACoreObject();
	virtual ~ACoreObject();

	DECLARE_GET_TYPENAME(ACoreObject)
public:
	static void InitializeGlobalData();

	virtual void Free() { _bDestory = true; }
	virtual String ToContext() const override;

	bool IsDestory() const { return _bDestory; }
private:
	bool		_bDestory;
};

SPACE_END
