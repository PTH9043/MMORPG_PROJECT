#pragma once

SPACE_BEGIN(Core)

/*
----------------------------------------
BASE ALLOCATOR
----------------------------------------
*/
/*
@ Date: 2023-12-30
@ Writer: ������
@ Explain
- �⺻���� �޸� �Ҵ�� Delete�� �ð� �ִ� Ŭ�����̴�.
*/
class CORE_DLL UBaseAllocator {
public:
	/*
	@ Date: 2023-12-30
	@ Writer: ������
	*/
	static void* Alloc(uint64 size);
	/*
	@ Date: 2023-12-30
	@ Writer: ������
	*/
	static void Release(void* ptr);
};


/*
----------------------------------------
BASE ALLOCATOR
----------------------------------------
POOL ALLOCATOR
----------------------------------------
*/
/*
@ Date: 2023-12-31, Writer: ������
@ Explain
- �޸� Ǯ ��ü �Ҵ��� ���� Ŭ����
*/
class CORE_DLL UPoolAllocator {
public:
	/*
	@ Date: 2023-12-30
	@ Writer: ������
	*/
	static void* Alloc(uint64 size);
	/*
	@ Date: 2023-12-30
	@ Writer: ������
	*/
	static void Release(void* ptr);
};



/*
----------------------------------------
POOL ALLOCATOR
----------------------------------------
STL ALLOCATOR
----------------------------------------
*/

template<class T>
class USTLAllocator {
public:
	using value_type = T;

	USTLAllocator() {}

	template<class Other>
	USTLAllocator(const USTLAllocator<Other>&) {}

	T* allocate(size_t count)
	{
		const size_t size = count * sizeof(T);
		return static_cast<T*>(UPoolAllocator::Alloc(size));
	}
	void deallocate(T* ptr, size_t count)
	{
		UPoolAllocator::Release(ptr);
	}

	template<typename U>
	bool operator==(const USTLAllocator<U>&) { return true; }

	template<typename U>
	bool operator!=(const USTLAllocator<U>&) { return false; }
};

/*
----------------------------------------
STL ALLOCATOR
----------------------------------------
MEMORY ALLOC FUNC
----------------------------------------
*/

template<class Type, class... Args>
Type* mnew(Args&&... args)
{
	Type* memory = static_cast<Type*>(UPoolAllocator::Alloc(sizeof(Type)));
	new(memory)Type(std::forward<Args>(args)...); // placement new
	return memory;
}

template<class Type>
Type* allocbuffer(size_t bufferSize)
{
	Type* memory = static_cast<Type*>(UPoolAllocator::Alloc(bufferSize));
	::memset(memory, 0, bufferSize);
	return memory;
}

template<class Type>
void mdelete(Type* obj)
{
	obj->~Type();
	UPoolAllocator::Release(obj);
}

template <class Type>
void releasebuffer(Type* obj)
{
	UPoolAllocator::Release(obj);
}

SPACE_END