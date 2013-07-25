#include "ObjectSerialiser.h"
#include "ObjectDeserialiser.h"
#include "PointerContainer.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointerContainer::Class(void)
{
	Pointer(mp.This());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CPointerContainer> CPointerContainer::Init(CPointer pPointer)
{
	Class();
	mp = pPointer;
	return this;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointerContainer::KillData(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CPointerContainer::Save(CObjectSerialiser* pcFile)
{
	return pcFile->WritePointer(mp);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CPointerContainer::Load(CObjectDeserialiser* pcFile)
{
	Class();

	return pcFile->ReadPointer(mp.This());
}
