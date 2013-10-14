#include "BaseObject.h"
#include "HollowObject.h"
#include "Objects.h"
#include "HollowEmbeddedObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CHollowEmbeddedObject::Save(CObjectSerialiser* pcFile)
{
	return FALSE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CHollowEmbeddedObject::Load(CObjectDeserialiser* pcFile)
{
	return FALSE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CHollowEmbeddedObject::RemoveTo(CEmbeddedObject* pcTo)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CHollowEmbeddedObject::GetNumEmbedded(void)
{
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CEmbeddedObject* CHollowEmbeddedObject::GetEmbeddedObject(int iIndex)
{
	if (iIndex == 0)
	{
		return this;
	}

	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CHollowEmbeddedObject::GetDistToRoot(void)
{
	return UNATTACHED_DIST_TO_ROOT;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CHollowEmbeddedObject::IsHollow(void)
{
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CBaseObject* CHollowEmbeddedObject::Dehollow(void)
{
	CBaseObject*	pcEmbedding;
	int				iEmbeddedIndex;
	CBaseObject*	pcThisDehollowed;

	iEmbeddedIndex = GetEmbeddedIndex();

	pcEmbedding = mpcEmbedded->Dehollow();
	pcThisDehollowed = (CBaseObject*)pcEmbedding->GetEmbeddedObject(iEmbeddedIndex);
	return pcThisDehollowed;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CHollowEmbeddedObject::GetEmbeddedIndex(void)
{
	return mpcEmbedded->GetEmbeddedIndex(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CHollowEmbeddedObject::KillDontFree(void)
{
	KillInternalData();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CHollowObject* CHollowEmbeddedObject::GetHollowObject(void)
{
	return (CHollowObject*)mpcEmbedded;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CHollowEmbeddedObject::AddHeapFrom(CBaseObject* pcFromObject)
{
	CHollowObject*	pcHollow;

	pcHollow = GetHollowObject();
	pcHollow->AddHeapFrom(pcFromObject);
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CHollowEmbeddedObject::RemoveHeapFrom(CBaseObject* mpcEmbedding)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CHollowEmbeddedObject::TryKill(BOOL bKillIfNoRoot)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CHollowEmbeddedObject::SetDistToRootAndSetPointedTosExpectedDistToRoot(int iDistToRoot)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CObjects* CHollowEmbeddedObject::GetObjects(void)
{
	CHollowObject*	pcHollow;

	pcHollow = GetHollowObject();
	return pcHollow->GetObjects();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CStackPointers* CHollowEmbeddedObject::GetStackPointers(void)
{
	CObjects*	pcObjects;

	pcObjects = GetObjects();
	if (pcObjects)
	{
		return pcObjects->GetStackPointers();
	}
	else
	{
		return NULL;
	}
}

