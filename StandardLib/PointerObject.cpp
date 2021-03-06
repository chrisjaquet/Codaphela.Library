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
#include "BaseLib/Define.h"
#include "BaseLib/Log.h"
#include "Object.h"
#include "HollowObject.h"
#include "ObjectDeserialiser.h"
#include "ObjectRemapFrom.h"
#include "PointerObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void LogPointerDebug(CPointer* pvThis, char* szMethod)
{
#ifdef DEBUG_POINTER
#ifdef DEBUG
	char*	szEmbeddingClass;
	char*	szEmbeddingName;
	char*	szEmbeddingIndex;
	char*	szEmbeddingAddress;

	CObject*	pcEmbedding;

	pcEmbedding = pvThis->Embedding();
	if (pcEmbedding != NULL)
	{
		szEmbeddingClass = pcEmbedding->ClassName();
		szEmbeddingIndex = IndexToString(pcEmbedding->GetOI());
		szEmbeddingName = pcEmbedding->GetName();
		szEmbeddingAddress = PointerToString(pcEmbedding);
		gcLogger.Debug2(PointerToString(pvThis), "->", szMethod, " [Embedding ", szEmbeddingClass, ": ", szEmbeddingIndex, " ", szEmbeddingName, " (", szEmbeddingAddress, ")]", NULL);
	}
	else
	{
		gcLogger.Debug2(PointerToString(pvThis), "->", szMethod, " [Embedding NULL]", NULL);
	}

	
#endif // DEBUG
#endif // DEBUG_POINTER
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer::CPointer()
{
	mpcObject = NULL;
	mpcEmbedding = NULL;

	LOG_POINTER_DEBUG();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer::CPointer(CPointer& cPointer)
{
	mpcEmbedding = NULL;
	mpcObject = NULL;

	LOG_POINTER_DEBUG();

	PointTo(cPointer.mpcObject, FALSE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer::CPointer(CEmbeddedObject* pcObject)
{
	mpcEmbedding = NULL;
	mpcObject = NULL;

	LOG_POINTER_DEBUG();

	PointTo(pcObject, FALSE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer::~CPointer()
{
	LOG_POINTER_DEBUG();

	if (mpcObject)
	{
		mpcObject->RemoveStackFromTryKill(this, FALSE);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::operator = (CEmbeddedObject* pcObject)
{
	LOG_POINTER_DEBUG();

	PointTo(pcObject, TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::operator = (CPointer& pcPointer)
{
	LOG_POINTER_DEBUG();

	PointTo(pcPointer.mpcObject, TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CEmbeddedObject* CPointer::operator -> ()
{
	if ((mpcObject) && (mpcObject->IsHollow()))
	{
		mpcObject = mpcObject->Dehollow();
	}
	return mpcObject;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CEmbeddedObject* CPointer::operator & ()
{
	if ((mpcObject) && (mpcObject->IsHollow()))
	{
		mpcObject = mpcObject->Dehollow();
	}
	return mpcObject;
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CPointer::operator ! ()
{
	return mpcObject == NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::UnsafeClearObject(void)
{
	mpcObject = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::SetEmbedding(CObject* pcEmbedding)
{
	mpcEmbedding = pcEmbedding;
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::UnsafePointTo(CEmbeddedObject* pcNewObject)
{
	mpcObject = pcNewObject;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::PointTo(CEmbeddedObject* pcNewObject, BOOL bKillIfNoRoot)
{
	CEmbeddedObject*	pcOldObject;

	if (mpcObject != pcNewObject)
	{
		pcOldObject = mpcObject;
		mpcObject = pcNewObject;

		if (IsEmbeddingAllocatedInObjects())
		{			
			if (pcOldObject)
			{
				if (mpcObject)
				{
					mpcObject->AddHeapFrom(mpcEmbedding, FALSE);
				}
				pcOldObject->RemoveHeapFrom(mpcEmbedding, TRUE);
			}
			else if (mpcObject)
			{
				mpcObject->AddHeapFrom(mpcEmbedding, TRUE);
			}
		}
		else
		{
			if (pcOldObject)
			{
				pcOldObject->RemoveStackFromTryKill(this, bKillIfNoRoot);
			}

			if (mpcObject)
			{
				mpcObject->AddStackFrom(this);
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CEmbeddedObject* CPointer::Return(void)
{
	CEmbeddedObject*	pOldObject;

	//Call this method when you need to return a pointers object but no other 
	//pointers point to the object and this pointers destructor must not destroy the object.

	pOldObject = mpcObject;
	mpcObject->PrivateRemoveStackFrom(this);
	mpcObject = NULL;
	return pOldObject;
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CPointer::IsNotNull(void)
{
	return mpcObject != NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CPointer::IsNull(void)
{
	return mpcObject == NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer* CPointer::This(void)
{
	//This method should only *ever* be called whilst in the Load method on a CObject
	return this;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CEmbeddedObject* CPointer::Object(void)
{
	return mpcObject;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CEmbeddedObject** CPointer::ObjectPtr(void)
{
	return &mpcObject;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CBaseObject* CPointer::BaseObject(void)
{
	if (mpcObject && mpcObject->IsBaseObject())
	{
		return (CBaseObject*)mpcObject;
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
CObject* CPointer::Embedding(void)
{
	return mpcEmbedding;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CEmbeddedObject* CPointer::Dereference(void)
{
	if ((mpcObject) && (mpcObject->IsHollow()))
	{
		mpcObject = mpcObject->Dehollow();
	}
	return mpcObject;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CPointer::MorphInto(CEmbeddedObject* pcNew)
{
	CObjectRemapFrom	cRemapper;
	int					iCount;

	iCount = cRemapper.Remap(mpcObject, pcNew, FALSE);

	return iCount;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CPointer::IsHollow(void)
{
	if (mpcObject)
	{
		return mpcObject->IsHollow();
	}
	else
	{
		return FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CPointer::Load(CObjectDeserialiser* pcFile)
{
	if (mpcObject)
	{
		if (!mpcObject->IsHollow())
		{
			return mpcObject->Load(pcFile);
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CPointer::GetDistToRoot(void)
{
	if (mpcObject)
	{
		return mpcObject->GetDistToRoot();
	}
	else
	{
		return -1;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
OIndex CPointer::GetIndex(void)
{
	if (mpcObject)
	{
		return mpcObject->GetOI();
	}
	else
	{
		return NULL_O_INDEX;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CPointer::GetName(void)
{
	if (mpcObject && mpcObject->IsNamed())
	{
		return mpcObject->GetName();
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
BOOL CPointer::IsNamed(void)
{
	if (mpcObject)
	{
		return mpcObject->IsNamed();
	}
	else
	{
		return FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CPointer::ClassName(void)
{
	if (mpcObject)
	{
		return mpcObject->ClassName();
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
BOOL CPointer::IsDirty(void)
{
	if (mpcObject)
	{
		return mpcObject->IsDirty();
	}
	else
	{
		return FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CPointer::IsEmbeddingAllocatedInObjects(void)
{
	if (mpcEmbedding)
	{
		return mpcEmbedding->IsAllocatedInObjects();
	}
	else
	{
		return FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::Kill(void)
{
	//This method exists so that it's object can be killed without invoking -> and potentially loading it first.
	if (mpcObject)
	{
		return mpcObject->Kill();
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::ClearIndex(void)
{
	if (mpcObject)
	{
		mpcObject->ClearIndex();
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::AssignObject(CEmbeddedObject* pcObject)
{
	mpcObject = pcObject;
	if (mpcObject)
	{
		mpcObject->AddStackFrom(this);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::AddHeapFrom(CBaseObject* pcFrom)
{
	if (mpcObject)
	{
		mpcObject->AddHeapFrom(pcFrom, TRUE);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::DumpFroms(void)
{
	CBaseObject* pvBaseObject = BaseObject();

	if (pvBaseObject)
	{
		pvBaseObject->DumpFroms();
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::DumpPointerTos(void)
{
	CBaseObject* pvBaseObject = BaseObject();

	if (pvBaseObject)
	{
		pvBaseObject->DumpPointerTos();
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPointer::Dump(void)
{
	CChars			sz;
	CBaseObject*	pvBaseObject = BaseObject();

	if (pvBaseObject)
	{
		pvBaseObject->Dump();
	}
	else
	{
		sz.Init("NULL\n");
		sz.Dump();
		sz.Kill();
	}
}

