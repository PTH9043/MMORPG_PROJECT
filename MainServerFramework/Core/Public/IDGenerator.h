#pragma once

SPACE_BEGIN(Core)

class IDGenerator {
public:
	static int64 GenComponentID() { return _ComponentIDGen.fetch_add(1, std::memory_order_relaxed); }
	static int64 GenObjectID() { return _ObjectIDGen.fetch_add(1, std::memory_order_relaxed); }
	static int64 GenManger() { return  _ManagerIDGen.fetch_add(1, std::memory_order_relaxed); }

private:
	static Atomic_int64 _ComponentIDGen;
	static Atomic_int64 _ObjectIDGen;
	static Atomic_int64 _ManagerIDGen;
};

SPACE_END
