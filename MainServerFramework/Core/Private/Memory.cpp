#include "CoreDefines.h"
#include "Memory.h"

namespace Core
{
	// AMemoryPool 생성자: 지정된 크기의 메모리 풀을 초기화
	AMemoryPool::AMemoryPool(const uint64 allocatedSize) :
		_AllocatedSize{ allocatedSize }
	{
	}

	// 메모리 풀 소멸자: 내부 큐에 남아 있는 메모리를 해제
	AMemoryPool::~AMemoryPool()
	{
		for (int32 i = 0; i < CoreStatic::MAX_THREAD_NUM; ++i)
		{
			while (!_MemoryQueue.empty())
			{
				AMemoryHeader* header = nullptr;
				_MemoryQueue.try_pop(header);
				::free(header);
			}
		}
	}

	// 메모리 반환: 풀에 재사용할 수 있도록 푸시
	void AMemoryPool::Push(AMemoryHeader* ptr)
	{
		_MemoryQueue.push(std::move(ptr));
	}

	// 메모리 요청: 풀에서 하나 꺼내거나 없으면 새로 malloc
	AMemoryHeader* AMemoryPool::Pop()
	{
		AMemoryHeader* Header = nullptr;

		if (!_MemoryQueue.empty())
		{
			_MemoryQueue.try_pop(Header);
		}

		if (nullptr == Header)
		{
			Header = reinterpret_cast<AMemoryHeader*>(std::malloc(_AllocatedSize));
		}

#ifdef USE_DEBUG
		assert(Header->GetAllocatedSize() != 0);
#endif 
		return Header;
	}

	/*
	-------------------------------
	MEMORYPOOL
	------------------------------
	MEMORYPOOLHANDLER
	------------------------------
	*/

	AMemoryPoolHandler::AMemoryPoolHandler(uint64 size) :
		_MemoryPool{nullptr}
	{
		_MemoryPool = std::make_unique<AMemoryPool>(size);
	}

	AMemoryPoolHandler::~AMemoryPoolHandler()
	{
		_MemoryPool.reset();
	}

	void* AMemoryPoolHandler::Allocate(uint64 size)
	{
		AMemoryHeader* header = nullptr;
		if (size > MAX_ALLOCATED_SIZE)
		{
			header = reinterpret_cast<AMemoryHeader*>(::malloc(size));
		}
		else
		{
			header = _MemoryPool->Pop();
		}

		return AMemoryHeader::AttachHeader(header, size);
	}

	void AMemoryPoolHandler::Release(AMemoryHeader* header, uint64 allocSize)
	{
		if (allocSize > MAX_ALLOCATED_SIZE)
		{
			::free(header);
		}
		else
		{
			::memset(header, 0, allocSize);
			_MemoryPool->Push(header);
		}
	}


	/*
	-------------------------------
	MEMORYPOOLHANDLER
	------------------------------
	MEMORYADMINSTER
	------------------------------
	*/

	AMemoryAdiminstor::POOLTABLE			AMemoryAdiminstor::_PoolTable;
	AMemoryAdiminstor::MEMORYTABLE	AMemoryAdiminstor::_MemoryTable;

	void AMemoryAdiminstor::InitializMemoryAdiminstor()
	{
		uint32 memoryIndex = 0;
		uint32 tableIndex = 0;

		// 작은 단위 메모리 (16~1024)
		InitializeMemoryPool(16, 1024, 16, OUT memoryIndex, OUT tableIndex);

		// 중간 단위 메모리 (1024~2048)
		InitializeMemoryPool(1024, 2048, 32, OUT memoryIndex, OUT tableIndex);

		// 큰 단위 메모리 (2048~MAX)
		InitializeMemoryPool(2048, MAX_ALLOCATED_SIZE, 64, OUT memoryIndex, OUT tableIndex);
	}

	void AMemoryAdiminstor::ReleaseMemoryAdiminstor()
	{
		for (auto& iter : _PoolTable)
		{
			delete iter;
		}
	}

	// 메모리 할당 함수: 지정 크기의 메모리 반환
	void* AMemoryAdiminstor::Allocate(uint64 size)
	{
		std::atomic_thread_fence(std::memory_order_seq_cst);
		uint64 allocSize = size + CoreFunc::GetTypeSize<AMemoryHeader>();
		return _PoolTable[allocSize]->Allocate(allocSize);
	}

	// 메모리 반환 함수: 풀에 다시 넣거나 free
	void AMemoryAdiminstor::Release(void* ptr)
	{
		AMemoryHeader* Header = AMemoryHeader::DetachHeader(ptr);
		std::atomic_thread_fence(std::memory_order_seq_cst);
		const uint64 allocSize = Header->GetAllocatedSize();
		assert(allocSize > 0);

		if (allocSize > MAX_ALLOCATED_SIZE)
		{
			::free(Header);
		}
		else
		{
			::memset(Header, 0, allocSize);
			_PoolTable[allocSize]->Release(Header, allocSize);
		}
	}

	void AMemoryAdiminstor::InitializeMemoryPool(uint32 startSize, uint32 endSize, 
		uint32 stepSize, IN uint32& memoryIndex, IN uint32& tableIndex)
	{
		for (uint32 size = startSize; size < endSize; size += stepSize)
		{
			AMemoryPoolHandler* pool = new AMemoryPoolHandler(size);
			while (tableIndex <= size)
			{
				_PoolTable[memoryIndex++] = pool;
			}
		}
	}
}
