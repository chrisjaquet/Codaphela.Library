#include "GlobalMemoryAllocator.h"


CMemory					gcMemory;
CGlobalMemoryAllocator	gcMemoryAllocator;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CGlobalMemoryAllocator::GetName(void)
{
	return "CGlobalMemoryAllocator";
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* CGlobalMemoryAllocator::Malloc(size_t tSize)
{
	return gcMemory.Add((unsigned int)tSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* CGlobalMemoryAllocator::Realloc(void* pv, size_t tSize)
{
	void*	pvNew;

	pvNew = gcMemory.Grow(pv, (unsigned int)tSize);
	return pvNew;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGlobalMemoryAllocator::Free(void* pv)
{
	gcMemory.Remove(pv);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CGlobalMemoryAllocator::IsLocal(void)
{
	return FALSE;
}

