#pragma once

SPACE_BEGIN(Core)

/*
----------------------------------------
BASE ALLOCATOR
----------------------------------------
*/
/*
@ Date: 2023-12-30
@ Writer: 박태현
@ Explain
- 기본적인 메모리 할당과 Delete를 맡고 있는 클래스이다.
*/
class CORE_DLL UBaseAllocator {
public:
	/*
	@ Date: 2023-12-30
	@ Writer: 박태현
	*/
	static void* Alloc(uint64 size);
	/*
	@ Date: 2023-12-30
	@ Writer: 박태현
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
@ Date: 2023-12-31, Writer: 박태현
@ Explain
- 메모리 풀 객체 할당을 위한 클래스
*/
class CORE_DLL UPoolAllocator {
public:
	/*
	@ Date: 2023-12-30
	@ Writer: 박태현
	*/
	static void* Alloc(uint64 size);
	/*
	@ Date: 2023-12-30
	@ Writer: 박태현
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