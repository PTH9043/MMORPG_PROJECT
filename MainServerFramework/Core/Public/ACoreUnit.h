#pragma once
#include "ILogEntity.h"

SPACE_BEGIN(Core)

template<class T>
class ACoreUnit abstract : public ILogEntity {
public:
	ACoreUnit() : _iCreateTime{ CoreFunc::CreateCurrentTime() } {}
	virtual ~ACoreUnit() { }

	DECLARE_GET_TYPENAME(ACoreUnit)

	virtual String ToContext() const override {
		return String("[") + GetTypeName()
			+ "] Time=" + Core::ToString(_iCreateTime);
	}

	template<class... Args>
		requires ConstructArgsCheck<T, Args...>
	static T* Create(Args&&... args) {
		return mnew<T>(std::forward<Args>(args)...);
	}

	virtual T* Clone() { return Create<T>(this); }

	const uint64 GetCreateTime() const { return _iCreateTime; }
private:
	const uint64		_iCreateTime;
};

SPACE_END