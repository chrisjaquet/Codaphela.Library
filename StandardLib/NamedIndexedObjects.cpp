/** ---------------- COPYRIGHT NOTICE, DISCLAIMER, and LICENSE ------------- **

Copyright (c) 2012 Andrew Paterson

This file is part of The Codaphela Project: Codaphela StandardLib

Codaphela StandardLib is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Codaphela StandardLib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Codaphela StandardLib.  If not, see <http://www.gnu.org/licenses/>.

** ------------------------------------------------------------------------ **/
#include "NamedIndexedObjects.h"
#include "NamedObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CNamedIndexedObjects::Init(void)
{
	mcNames.Init();
	mcObjects.Init();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CNamedIndexedObjects::Kill(void)
{
	mcObjects.Kill();
	mcNames.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CBaseObject* CNamedIndexedObjects::Get(OIndex oi)
{
	return (CBaseObject*)mcObjects.Get(oi);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CBaseObject* CNamedIndexedObjects::Get(char* szName)
{
	OIndex	oi;

	oi = mcNames.Get(szName);
	if (oi != INVALID_O_INDEX)
	{
		return Get(oi);
	}
	else
	{
		return NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CNamedIndexedObjects::Add(OIndex oi, CBaseObject* pvMemory, CBaseObject** pvExisting)
{
	if (pvExisting)
	{
		return mcObjects.AddOverwriteExisting(oi, pvMemory, (void**)pvExisting);
	}
	else
	{
		return mcObjects.Add(oi, pvMemory);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CNamedIndexedObjects::Remove(OIndex oi)
{
	mcObjects.Remove(oi);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CNamedIndexedObjects::AddWithID(CBaseObject* pvObject, OIndex oi, CBaseObject** ppvExisting)
{
	pvObject->SetObjectID(oi);
	return Add(oi, pvObject, ppvExisting);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CNamedIndexedObjects::AddWithIDAndName(CBaseObject* pvObject, OIndex oi, char* szName, CBaseObject** ppvExisting)
{
	CNamedObject*	pcNamed;
	BOOL			bResult;

	bResult = AddWithID(pvObject, oi, ppvExisting);
	if (!bResult)
	{
		return FALSE;
	}

	pcNamed = (CNamedObject*)pvObject;
	bResult = pcNamed->InitName(szName);

	mcNames.Add(pcNamed->GetOI(), szName);
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
OIndex CNamedIndexedObjects::NumObjects(void)
{
	return mcObjects.NumIndexed();
}

