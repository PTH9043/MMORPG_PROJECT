#pragma once
#include "ACoreManger.h"

SPACE_BEGIN(Core)

class AThreadManger :  public ACoreManger {
	using THREAD = std::thread;
	using THREADS = VECTOR<THREAD>;
	using THREADNAMES = UNORMAP<int32, String>;
	using THREADINDEXES = UNORMAP<int32, String>;
public:
	AThreadManger();
	virtual ~AThreadManger();
	DECLARE_GET_TYPENAME(AThreadManger)

	virtual EErrorState NativeConstruct(void* data = nullptr) override;
	void RegisterFunc(const THREADFUNC& callBack, void* _Data, const String& name);
	void Join();
private:
	static void ThreadJoin(const THREADFUNC& callBack, void* data, int32 currentThreadID);
private:
	int32							_ThreadNums;
	THREADS					_Threads;
	THREADNAMES		_ThreadNames;
	THREADINDEXES		_ThreadIndexes;
};

SPACE_END