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
#ifndef __ARRAY_COMMON_OBJECT_H__
#define __ARRAY_COMMON_OBJECT_H__
#include "Collection.h"
#include "ArrayCommonUnknown.h"


class CArrayCommonUnknown;
class CArrayCommonObject : public CCollection
{
BASE_FUNCTIONS(CArrayCommonObject);
protected:
	CArrayCommonUnknown		mcArray;
	BOOL					mbSubRoot;

public:
	Ptr<CArrayCommonObject>	Init(BOOL bUnique, BOOL bIgnoreNull, BOOL bPreserveOrder, int iChunkSize);
	void					Class(void);
	void					Kill(void);

	void					Add(CPointer& pObject);
	void					AddAll(CArrayCommonObject* pcArray);
	void					Set(int iIndex, CPointer& pObject);
	BOOL					Remove(CPointer& pObject);
	BOOL					Remove(CBaseObject* pcObject);
	void					RemoveAll(void);

	int						NumElements(void);
	int						NonNullElements(void);

	void					MakeSubRoot(void);
	BOOL					IsSubRoot(void);
	void					SetPointerTosExpectedDistToRoot(int iDistToRoot);

	int						NumPointerTos(void);
	int						BaseNumPointerTos(void);
	void					GetPointerTos(CArrayTemplateEmbeddedObjectPtr* papcTos);
	void					BaseGetPointerTos(CArrayTemplateEmbeddedObjectPtr* papcTos);
	BOOL					ContainsPointerTo(CEmbeddedObject* pcEmbedded);
	void					RemoveAllPointerTosDontKill(void);
	void					RemoveAllPointerTos(void);
	void					CollectAndClearPointerTosInvalidDistToRootObjects(CDistCalculatorParameters* pcParameters);

	BOOL					Save(CObjectSerialiser* pcFile);
	BOOL					Load(CObjectDeserialiser* pcFile);

	CBaseObject*			UnsafeGet(int iIndex);
	BOOL					UnsafeRemove(CBaseObject* pcObject);
	CEmbeddedObject*		GetEmbeddedObject(unsigned short int iIndex);

	void					BaseValidatePointerTos(void);
	void					ValidatePointerTos(void);
	void					ValidateConsistency(void);

protected:
	void	KillInternalData(void);
	void	KillData(void);
	void	RemovePointerTo(CEmbeddedObject* pcTo);
	void	BaseRemoveAllPointerTosDontKill(void);
	void	BaseRemoveAllPointerTos(void);
	int		RemapPointerTos(CEmbeddedObject* pcOld, CEmbeddedObject* pcNew);
	void	SetPointedTosDistToRoot(int iDistToRoot);
	void	UpdateEmbeddedObjectTosDistToRoot(CDistToRootEffectedFroms* pcEffectedFroms, int iExpectedDist);
	void	UpdateAttachedEmbeddedObjectPointerTosDistToRoot(CDistCalculatorParameters* pcParameters, int iExpectedDist);
	void	ClearEmbeddedObjectTosUpdatedTosFlags(void);
	void	UpdateEmbeddedObjectTosDetached(CDistDetachedFroms* pcDetached, CDistToRootEffectedFroms* pcEffectedFroms);
	void	UpdateEmbeddedObjectTosUnattached(CDistToRootEffectedFroms* pcEffectedFroms);
};


#endif // __ARRAY_COMMON_OBJECT_H__

