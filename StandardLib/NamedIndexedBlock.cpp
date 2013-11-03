#include <shlwapi.h>  //This needs to be replaced with "BaseLib/String.h" 
#include "BaseLib/Define.h"
#include "BaseLib/FastMemset.h"
#include "BaseObject.h"
#include "NamedIndexedBlock.h"


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
int CompareNamedIndexedBlock(const void* arg1, const void* arg2)
{
	CNamedIndexedBlock*	ps1;
	CNamedIndexedBlock*	ps2;

	ps1 = (CNamedIndexedBlock*)arg1;
	ps2 = (CNamedIndexedBlock*)arg2;

	return StrCmp(ps1->Name(), ps2->Name());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CNamedIndexedBlock::Name(void)
{
	return mszName;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
OIndex CNamedIndexedBlock::Id(void)
{
	return moi;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CNamedIndexedBlock::Set(char* szName, OIndex oi)
{
	StrCpy(mszName, szName);
	moi = oi;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CNamedIndexedBlock::IsEmpty(void)
{
	return mszName[0] == 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CNamedIndexedBlock::CompareTo(CNamedIndexedBlock* pcOther)
{
	return CompareNamedIndexedBlock(this, pcOther);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CNamedIndexedBlock::Zero(int iBlockWidth)
{
	memset_fast(this, 0, iBlockWidth);
	moi = INVALID_O_INDEX;
}

