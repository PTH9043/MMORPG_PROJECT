#pragma once

SPACE_BEGIN(Core)

enum
{
	POOL_COUNT = (1024 / 16) + (1024 / 32) + (2048 / 64),
	MAX_ALLOCATED_SIZE = 4096
};

/// ---------------------------------------------------
/// AMemoryHeader
/// - ���� �޸� ��� �տ� �ٴ� ��Ÿ������ ����
/// - �Ҵ�� ��ü ũ�� ���� ���� �����ϸ�, ��� ��ȯ �� ����
/// ---------------------------------------------------
class AMemoryHeader {
public:
	AMemoryHeader() : _iAllocatedSize{ 0L } {}
	AMemoryHeader(int64 size) : _iAllocatedSize{ size } {}

	/// ����� �޸� ��� �տ� ���̰�, ���� ������ �����͸� ��ȯ
	/// @param T - ��ȯ�� ������ Ÿ��
	/// @param ptr - ����� �� �޸� �ּ� (MemoryHeader*�� ĳ���õ� ���¿��� ��)
	/// @param size - ���� ������ ũ��
	/// @return T* - ��� �ڿ� ��ġ�� ���� �������� ���� �ּ�
	static void* AttachHeader(AMemoryHeader* ptr, int64 size)
	{
		new(ptr)(AMemoryHeader)(size);
		return reinterpret_cast<void*>(++ptr);
	}

	/// ������ �����Ϳ��� ��� �����ͷ� �ǵ���
	/// @param ptr - ������ ������ (AttachHeader�� ���� T* �Ǵ� void*)
	/// @return MemoryHeader* - �ش� ������ �տ� ���� ��� ������
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
/// - ���� ũ�� �޸� ����� �����ϴ� Ǯ
/// - ���� ť�� ���� ���� ������ ����� ����
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
/// - �޸� Ǯ�� �ٷ�� �ڵ鷯
/// ---------------------------------------------------
class AMemoryPoolHandler {
public:
	AMemoryPoolHandler(uint64 size);
	~AMemoryPoolHandler();
	/// ��û�� ũ�⸸ŭ �޸� �Ҵ�
	/// - MAX_ALLOCATED_SIZE ���� �� Ǯ���� ����
	/// - �ʰ� �� malloc ���
	void* Allocate(uint64 size);

	/// �޸� ��ȯ
	/// - ��� ũ�� Ȯ�� �� Ǯ�� �ǵ����ų� free
	void Release(AMemoryHeader* header, uint64 allocSize);
private:
	std::unique_ptr<AMemoryPool>		_MemoryPool;
};

/// ---------------------------------------------------
/// AMemoryAdiminstor
/// - �پ��� ũ���� �޸� Ǯ�� �ʱ�ȭ�ϰ� ����
/// - Allocate / Release ���� �޸� ��� ����ȭ
/// ---------------------------------------------------
/// 
class AMemoryAdiminstor {
	using POOLTABLE = ARRAY<AMemoryPoolHandler*, MAX_ALLOCATED_SIZE>;
	using MEMORYTABLE = ARRAY<AMemoryPoolHandler*, POOL_COUNT>;
public:
	static void InitializMemoryAdiminstor();
	static void ReleaseMemoryAdiminstor();

	/// ��û�� ũ�⸸ŭ �޸� �Ҵ�
	/// - MAX_ALLOCATED_SIZE ���� �� Ǯ���� ����
	/// - �ʰ� �� malloc ���
	static void* Allocate(uint64 size);

	/// �޸� ��ȯ
	/// - ��� ũ�� Ȯ�� �� Ǯ�� �ǵ����ų� free
	static void Release(void* ptr);
private:
	static void InitializeMemoryPool(uint32 startSize, uint32 endSize,
		uint32 stepSize, IN uint32& memoryIndex, IN uint32& tableIndex);

private:
	static POOLTABLE			_PoolTable;
	static MEMORYTABLE	_MemoryTable;
};

SPACE_END