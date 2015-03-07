#include "DataMacro.h"
#include "ScratchPadAllocator.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CScratchPadAllocator::Init(void)
{
	mcScratchPad.Init();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CScratchPadAllocator::Init(int iChunkSize)
{
	mcScratchPad.Init(iChunkSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CScratchPadAllocator::Kill(void)
{
	mcScratchPad.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* CScratchPadAllocator::Malloc(size_t tSize)
{
	return mcScratchPad.Add(tSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* CScratchPadAllocator::Realloc(void* pv, size_t tSize)
{
	SSPNode*	psNode;
	void*		pvNew;

	pvNew = mcScratchPad.Add(tSize); 
	psNode =  DataGetHeader<SSPNode, void>(pv);
	psNode->bUsed = FALSE;
	if (psNode->iSize > tSize)
	{
		memcpy(pvNew, pv, tSize);
	}
	else
	{
		memcpy(pvNew, pv, psNode->iSize);
	}
	return pvNew;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CScratchPadAllocator::Free(void* pv)
{
	SSPNode*	psNode;

	psNode =  DataGetHeader<SSPNode, void>(pv);
	psNode->bUsed = FALSE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CScratchPad* CScratchPadAllocator::GetScratchPad(void)
{
	return &mcScratchPad;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CScratchPadAllocator::GetName(void)
{
	return "CScratchPadAllocator";
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CScratchPadAllocator::Read(CFileReader* pcFileReader)
{
	SScratchPadParams	sParams;

	if (!pcFileReader->ReadData(&sParams, sizeof(SScratchPadParams)))
	{
		return FALSE;
	}

	mcScratchPad.Init(sParams.iChunkSize);
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CScratchPadAllocator::Write(CFileWriter* pcFileWriter)
{
	SScratchPadParams	sParams;

	mcScratchPad.GetParams(&sParams);

	if (!pcFileWriter->WriteData(&sParams, sizeof(SScratchPadParams)))
	{
		return FALSE;
	}
	return TRUE;
}

