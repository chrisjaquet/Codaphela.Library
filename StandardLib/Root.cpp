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
#include "Objects.h"
#include "ObjectSerialiser.h"
#include "ObjectDeserialiser.h"
#include "Root.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CRoot::CRoot()
{
	SetDistToRoot(ROOT_DIST_TO_ROOT);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRoot::Init(void)
{
	Pointer(mpObjects.This());
	mpcObjectsAllocatingFrom = &gcObjects;
	mpObjects = mpcObjectsAllocatingFrom->Add<CSet>();
	mpObjects->Init(1024);
	mpObjects->MakeSubRoot();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRoot::Init(CObjects* pcObjectsAllocatingFrom)
{
	Pointer(mpObjects.This());
	mpcObjectsAllocatingFrom = pcObjectsAllocatingFrom;
	mpObjects = mpcObjectsAllocatingFrom->Add<CSet>();
	mpObjects->Init(1024);
	mpObjects->MakeSubRoot();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRoot::KillData(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRoot::Add(CPointerObject pObject)
{
	mpObjects->Add(pObject);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRoot::Remove(CPointerObject pObject)
{
	mpObjects->Remove(pObject);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRoot::RemoveAll(void)
{
	mpObjects->RemoveAll();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CRoot::IsRoot(void)
{
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CRoot::IsSubRoot(void)
{
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CRoot::Save(CObjectSerialiser* pcFile)
{
	return pcFile->WritePointer(mpObjects);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CRoot::Load(CObjectDeserialiser* pcFile)
{
	BOOL	bResult;

	mpcObjectsAllocatingFrom = &gcObjects;
	bResult = pcFile->ReadPointer(Pointer(mpObjects.This()));
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointerObject CRoot::Get(char* szObjectName)
{
	SSetIterator	sIter;
	CPointerObject	pObject;
	char*			szName;

	if ((szObjectName == NULL) || (szObjectName[0] == '\0'))
	{
		return ONull;
	}

	pObject = mpObjects->StartIteration(&sIter);
	while (pObject.IsNotNull())
	{
		szName = pObject.GetName();
		if (szName != NULL)
		{
			if (strcmp(szObjectName, szName) == 0)
			{
				return pObject;
			}
		}
		pObject = mpObjects->Iterate(&sIter);
	}

	return ONull;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer<CSet> CRoot::GetAll(void)
{
	return mpObjects;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CSet* CRoot::TestGetSet(void)
{
	return	&mpObjects;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CRoot::IsSetHollow(void)
{
	return mpObjects.IsHollow();
}

