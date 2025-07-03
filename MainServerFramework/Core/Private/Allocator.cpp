#include "CoreDefines.h"
#include "Allocator.h"

SPACE_BEGIN(Core)

void* UBaseAllocator::Alloc(uint64  size)
{
	return ::malloc(size);
}

void UBaseAllocator::Release(void* ptr)
{
	::free(ptr);
}


/*
----------------------------------------
BASE ALLOCATOR
----------------------------------------
STOMP
----------------------------------------
*/

void* UPoolAllocator::Alloc(uint64 size)
{
	return AMemoryAdiminstor::Allocate(size);
}

void UPoolAllocator::Release(void* ptr)
{
	AMemoryAdiminstor::Release(ptr);
}

SPACE_END