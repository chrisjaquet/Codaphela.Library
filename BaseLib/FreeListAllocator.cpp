#include "FreeListAllocator.h"


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void CFreeListAllocator::Init(int iChunkSize, int iElementSize)
{
	mcFreeList.Init(iChunkSize, iElementSize);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void CFreeListAllocator::Init(int iChunkSize, int iElementSize, int iAlignment)
{
	mcFreeList.Init(iChunkSize, iElementSize, iAlignment);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void CFreeListAllocator::Init(int iChunkSize, int iElementSize, int iAlignment, int iOffset)
{
	mcFreeList.Init(iChunkSize, iElementSize, iAlignment, iOffset);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void CFreeListAllocator::Kill(void)
{
	mcFreeList.Kill();
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void* CFreeListAllocator::Malloc(size_t tSize)
{
	if (tSize > (size_t)mcFreeList.GetElementSize())
	{
		return NULL;
	}
	
	return mcFreeList.Add();
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void CFreeListAllocator::Free(void* pv)
{
	mcFreeList.Remove(pv);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void* CFreeListAllocator::Realloc(void* pv, size_t tSize)
{
	if (tSize > (size_t)mcFreeList.GetElementSize())
	{
		mcFreeList.Remove(pv);
		return NULL;
	}

	return pv;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
char* CFreeListAllocator::GetName(void)
{
	return "CFreeListAllocator";
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
CFreeList* CFreeListAllocator::GetFreeList(void)
{
	return &mcFreeList;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
BOOL CFreeListAllocator::Read(CFileReader* pcFileReader)
{
	SFreeListParams2	sParams;

	if (!pcFileReader->ReadData(&sParams, sizeof(SFreeListParams2)))
	{
		return FALSE;
	}

	mcFreeList.Init(sParams.iChunkSize, sParams.iElementSize, sParams.iAlignment, sParams.iOffset);
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
BOOL CFreeListAllocator::Write(CFileWriter* pcFileWriter)
{
	SFreeListParams2	sParams;

	mcFreeList.GetParams(&sParams);
	
	if (!pcFileWriter->WriteData(&sParams, sizeof(SFreeListParams2)))
	{
		return FALSE;
	}
	return TRUE;
}

