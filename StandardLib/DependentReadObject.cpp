#include "ObjectFileGeneral.h"
#include "DependentReadObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDependentReadObject::Init(CPointerHeader* pcObjectPtr)
{
	CPointerHeader*	pcThis;

	pcThis = this;
	memcpy_fast(pcThis, pcObjectPtr, sizeof(CPointerHeader));
	miFlags = 0;
	moiNew = INVALID_O_INDEX;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDependentReadObject::Kill(void)
{
	CPointerHeader::Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDependentReadObject::SetNewIndex(OIndex oiNew)
{
	moiNew = oiNew;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CDependentReadObject::IsNamed(void)
{
	return mcType == OBJECT_POINTER_NAMED;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CDependentReadObject::GetName(void)
{
	return mszObjectName.Text();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
OIndex CDependentReadObject::GetOldIndex(void)
{
	return moi;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
OIndex CDependentReadObject::GetNewIndex(void)
{
	return moiNew;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDependentReadObject::SetRead(void)
{
	miFlags |= DEPENDENT_READ_OBJECT_FLAG_READ;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CDependentReadObject::SetExisting(void)
{
	miFlags |= DEPENDENT_READ_OBJECT_FLAG_EXISTED;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CDependentReadObject::IsRead(void)
{
	return miFlags & DEPENDENT_READ_OBJECT_FLAG_READ;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CDependentReadObject::PreExisted(void)
{
	return miFlags & DEPENDENT_READ_OBJECT_FLAG_EXISTED;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CompareDependentReadObject(const void* ps1, const void* ps2)
{
	CDependentReadObject*	psObj1;
	CDependentReadObject*	psObj2;

	psObj1 = (CDependentReadObject*)ps1;
	psObj2 = (CDependentReadObject*)ps2;

	if (psObj1->moi < psObj2->moi)
	{
		return -1;
	}
	else if (psObj1->moi > psObj2->moi)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

