#pragma once

SPACE_BEGIN(Core)

enum
{
	POOL_COUNT = (1024 / 16) + (1024 / 32) + (2048 / 64),
	MAX_ALLOCATED_SIZE = 4096
};

/// ---------------------------------------------------
/// AMemoryHeader
/// - 실제 메모리 블록 앞에 붙는 메타데이터 구조
/// - 할당된 전체 크기 정보 등을 포함하며, 블록 반환 시 사용됨
/// ---------------------------------------------------
class AMemoryHeader {
public:
	AMemoryHeader() : _iAllocatedSize{ 0L } {}
	AMemoryHeader(int64 size) : _iAllocatedSize{ size } {}

	/// 헤더를 메모리 블록 앞에 붙이고, 실제 데이터 포인터를 반환
	/// @param T - 반환할 데이터 타입
	/// @param ptr - 헤더를 쓸 메모리 주소 (MemoryHeader*로 캐스팅된 상태여야 함)
	/// @param size - 실제 데이터 크기
	/// @return T* - 헤더 뒤에 위치한 실제 데이터의 시작 주소
	static void* AttachHeader(AMemoryHeader* ptr, int64 size)
	{
		new(ptr)(AMemoryHeader)(size);
		return reinterpret_cast<void*>(++ptr);
	}

	/// 데이터 포인터에서 헤더 포인터로 되돌림
	/// @param ptr - 데이터 포인터 (AttachHeader로 얻은 T* 또는 void*)
	/// @return MemoryHeader* - 해당 데이터 앞에 붙은 헤더 포인터
	static AMemoryHeader* DetachHeader(void* ptr)
	{
		return reinterpret_cast<AMemoryHeader*>(ptr) - 1;
	}
public:
	void UpdateAllocatedData(int64 allocatedSize)
	{
		_iAllocatedSize = allocatedSize;
	}

	const int64 GetAllocatedSize() const { return _iAllocatedSize; }
private:
	int64		_iAllocatedSize;
};


/// ---------------------------------------------------
/// AMemoryPool
/// - 고정 크기 메모리 블록을 관리하는 풀
/// - 내부 큐를 통해 재사용 가능한 블록을 저장
/// ---------------------------------------------------
class AMemoryPool {
	using MEMORYQUEUE = CONQUEUE<AMemoryHeader*>;
public:
	AMemoryPool(const uint64 allocatedSize);
	~AMemoryPool();

	void Push(AMemoryHeader* ptr);
	AMemoryHeader* Pop();
private:
	uint64	_AllocatedSize;
	MEMORYQUEUE _MemoryQueue;
};

/// ---------------------------------------------------
/// AMemoryPoolHandler
/// - 메모리 풀을 다루는 핸들러
/// ---------------------------------------------------
class AMemoryPoolHandler {
public:
	AMemoryPoolHandler(uint64 size);
	~AMemoryPoolHandler();
	/// 요청된 크기만큼 메모리 할당
	/// - MAX_ALLOCATED_SIZE 이하 → 풀에서 제공
	/// - 초과 시 malloc 사용
	void* Allocate(uint64 size);

	/// 메모리 반환
	/// - 블록 크기 확인 후 풀에 되돌리거나 free
	void Release(AMemoryHeader* header, uint64 allocSize);
private:
	std::unique_ptr<AMemoryPool>		_MemoryPool;
};

/// ---------------------------------------------------
/// AMemoryAdiminstor
/// - 다양한 크기의 메모리 풀을 초기화하고 관리
/// - Allocate / Release 통해 메모리 사용 최적화
/// ---------------------------------------------------
/// 
class AMemoryAdiminstor {
	using POOLTABLE = ARRAY<AMemoryPoolHandler*, MAX_ALLOCATED_SIZE>;
	using MEMORYTABLE = ARRAY<AMemoryPoolHandler*, POOL_COUNT>;
public:
	static void InitializMemoryAdiminstor();
	static void ReleaseMemoryAdiminstor();

	/// 요청된 크기만큼 메모리 할당
	/// - MAX_ALLOCATED_SIZE 이하 → 풀에서 제공
	/// - 초과 시 malloc 사용
	static void* Allocate(uint64 size);

	/// 메모리 반환
	/// - 블록 크기 확인 후 풀에 되돌리거나 free
	static void Release(void* ptr);
private:
	static void InitializeMemoryPool(uint32 startSize, uint32 endSize,
		uint32 stepSize, IN uint32& memoryIndex, IN uint32& tableIndex);

private:
	static POOLTABLE			_PoolTable;
	static MEMORYTABLE	_MemoryTable;
};

SPACE_END