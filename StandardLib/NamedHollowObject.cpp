#include "Objects.h"
#include "NamedObject.h"
#include "HollowEmbeddedObject.h"
#include "NamedHollowObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CNamedHollowObject::Kill(void)
{
	CHollowObject::Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CNamedHollowObject::KillIdentifiers(void)
{
	mon.Kill();
	CHollowObject::KillIdentifiers();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CBaseObject* CNamedHollowObject::Dehollow(void)
{
	return mpcObjectsThisIn->Dehollow(mon.Text());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CNamedHollowObject::GetName(void)
{
	return mon.Text();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CNamedHollowObject::IsNamed(void)
{
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CNamedHollowObject::InitName(char* szName)
{
	mon.Init(szName);
	if (mon.Length() < MAX_NAMED_OBJECT_NAME_LENGTH)
	{
		return TRUE;
	}
	mon.SetLength(MAX_NAMED_OBJECT_NAME_LENGTH-1);
	return FALSE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CEmbeddedObject* CNamedHollowObject::GetRemappedEmbeddedObject(int iIndex)
{
	CEmbeddedObject*	pcEmbedded;

	pcEmbedded = (CEmbeddedObject*)RemapSinglePointer(this, sizeof(CNamedHollowObject) + sizeof(CHollowEmbeddedObject)*(iIndex-1));
	return pcEmbedded;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CNamedHollowObject::ClearName(void)
{
	mon.Kill();
	mon.Init();
}
