#include "GlobalMemory.h"

CMemory					gcMemory;
CMemoryAllocator		gcMemoryAllocator;
BOOL					gbMemory = FALSE;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void MemoryInit(void)
{
	gcMemory.Init();
	gcMemoryAllocator.Init(&gcMemory);
	gbMemory = TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void MemoryInit(int iDefaultAlignment, BOOL bDefaultFreeListParams)
{
	gcMemory.Init(iDefaultAlignment, bDefaultFreeListParams);
	gcMemoryAllocator.Init(&gcMemory);
	gbMemory = TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void MemoryKill(void)
{
	gcMemory.Kill();
	gbMemory = FALSE;
}

