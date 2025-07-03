#pragma once
#include "ILogEntity.h"

SPACE_BEGIN(Core)

enum class EBaseType : int32 { None, Object, Manger };

class ACoreBase abstract : public AEnableSharedFromThis<ACoreBase> , public ILogEntity {
public:
	ACoreBase(EBaseType BaseType, int64 CoreID);
	virtual ~ACoreBase();

	DECLARE_GET_TYPENAME(ACoreBase)
	using value = ACoreBase;
public:
	template<class T>
	SHPTR<T> ThisShared()
	{
		static_assert(std::is_base_of<ACoreBase, T>::value, "T는 반드시 ACoreBase 파생이어야 합니다.");
		return static_shared_cast<T>(shared_from_this()); 
	}

	template<class T>
	WKPTR<T> ThisWeak() { return { ThisShared<T>() }; }

	virtual EErrorState NativeConstruct(void* data = nullptr) = 0;
	virtual String ToContext() const override;
	bool IsType(EBaseType type) const { return _eBaseType == type; }
	EBaseType GetBaseType() const { return _eBaseType; }
	int64 GetCoreID() const { return _iCoreID.load(); }
private:
	EBaseType		_eBaseType;
	Atomic_int64	_iCoreID;
};

SPACE_END