/** ---------------- COPYRIGHT NOTICE, DISCLAIMER, and LICENSE ------------- **

Copyright (c) 2009 Andrew Paterson

This file is part of The Codaphela Project: Codaphela BaseLib

Codaphela BaseLib is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Codaphela BaseLib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Codaphela BaseLib.  If not, see <http://www.gnu.org/licenses/>.

Microsoft Windows is Copyright Microsoft Corporation

** ------------------------------------------------------------------------ **/
#ifndef __ARRAY_TEMPLATE_MINIMAL_H__
#define __ARRAY_TEMPLATE_MINIMAL_H__
#include "Define.h"
#include "PointerRemapper.h"
#include "ErrorHandler.h"
#include "FileIO.h"


template <class M>
class CArrayTemplateMinimal
{
protected:
	int		miUsedElements;
	M*		mpvArray;

public:
	void	Init(void);
	void	Init(int iIgnored);
	void 	ReInit(void);
	void	Kill(void);
	void	Allocate(int iNum);
	BOOL	Reallocate(int iUsedElements);
	M*		Add(void);
	void	Add(M* pvData);
	void	Set(int iElementPos, M* pvData);
	M*		InsertAt(int iElementPos);
	void	InsertAt(M* pvData, int iElementPos);
	void	BatchInsertElements(int iFirstElementPos, int iNumInBatch, int iNumBatches, int iStrideToNextBatch);
	M*		SafeGet(int iElementPos);
	M*		Get(int iElementPos);
	BOOL	RemoveAt(int iElementPos, int bPreserveOrder = 0);
	BOOL	RemoveTail(void);
	void	BatchRemoveElements(int iFirstElementPos, int iNumInBatch, int iNumBatches, int iStrideToNextBatch);
	int		ByteSize(void);
	BOOL	SetArraySize(int iNum);
	M*		SetArraySize(int iNum, int iClearValue);
	int		NumElements(void);
	void 	Copy(CArrayTemplateMinimal<M>* pArray);
	void 	Zero(void);
	void	Zero(int iStart, int iEnd);
	void	QuickSort(int(* Func)(const void*, const void*));
	void	InsertIntoSorted(int(* Func)(const void*, const void*), M* pvElement);
	int 	Find(M* pData);
	int 	FindWithKey(M* pData, int iKeyOffset, int iKeySize);
	int		FindWithIntKey(int iKey, int iKeyOffset);
	int		FindInSorted(M* pData, int(* Func)(const void*, const void*), int bFindIfNone);
	int		BinarySearch(M* pData, int iLeft, int iRight, int(* Func)(const void*, const void*), int bFindIfNone);
	int 	AddIfUnique(M* pData);
	int 	AddIfUniqueKey(M* pData, int iKeyOffset, int iKeySize);
	int		GetAdjustedIndex(int iIndex);
	int		GetIndex(M* pvElement);
	int		GrowToNumElements(int iNumElements);
	int		GrowByNumElements(int iNumElements);
	M*		InsertNumElementsAt(int iNumElements, int iElementPos);
	M*		Tail(void);
	M*		GetData(void);
	void	FakeSetUsedElements(int iUsedElements);

	BOOL	Write(CFileWriter* pcFileWriter);
	BOOL	Read(CFileReader* pcFileReader);

protected:
	void*	Malloc(size_t tSize);
	void*	Realloc(void* pv, size_t iMemSize);
	void	Free(void* pv);
};


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::Init(void)
{
	miUsedElements = 0;
	mpvArray = NULL;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::Init(int iIgnored)
{
	Init();
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::ReInit(void)
{
	Kill();
	Init();
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::Kill(void)
{
	Free(mpvArray);
	mpvArray = NULL;
	miUsedElements = 0;
}

//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::Allocate(int iNum)
{
	Init();
	SetArraySize(iNum);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
BOOL CArrayTemplateMinimal<M>::Reallocate(int iUsedElements)
{
	M*	pvTemp;

	if (iUsedElements == 0)
	{
		if (mpvArray != NULL)
		{
			Free(mpvArray);
			mpvArray = NULL;
		}
		miUsedElements = 0;
		return TRUE;
	}

	pvTemp = (M*)Realloc(mpvArray, iUsedElements * sizeof(M));

	if (pvTemp != NULL)
	{
		miUsedElements = iUsedElements;
		mpvArray = pvTemp;
		return TRUE;
	}
	else
	{
		gcUserError.Set("CArrayTemplateMinimal, Out of memory.");
		return FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
M* CArrayTemplateMinimal<M>::Add(void)
{
	if (Reallocate(miUsedElements+1))
	{
		return &mpvArray[miUsedElements-1];
	}
	else
	{
		return NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::Add(M* pvData)
{
	M* pvTemp;

	pvTemp = Add();
	memcpy(pvTemp, pvData, sizeof(M));
}



//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
M* CArrayTemplateMinimal<M>::SafeGet(int iElementPos)
{
	if ((iElementPos < 0) || (iElementPos >= miUsedElements))
	{
		return NULL;
	}
	else
	{
		return &mpvArray[iElementPos];
	}
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
M* CArrayTemplateMinimal<M>::Get(int iElementPos)
{
	return &mpvArray[iElementPos];
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
BOOL CArrayTemplateMinimal<M>::RemoveAt(int iElementPos, int bPreserveOrder)
{
	M*	pvEnd;
	M*	pvElement;
	int	iUsedElements;

	iUsedElements = miUsedElements - 1;
	if (iElementPos < iUsedElements)
	{
		pvElement = Get(iElementPos);
		if (!bPreserveOrder)
		{
			pvEnd = Get(iUsedElements);
			memcpy(pvElement, pvEnd, sizeof(M));
		}
		else
		{
			memmove(pvElement, (M*)((ENGINE_SIZE_T) pvElement + sizeof(M)), sizeof(M) * (iUsedElements - iElementPos));
		}
	}

	return Reallocate(iUsedElements);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
BOOL CArrayTemplateMinimal<M>::RemoveTail(void)
{
	return RemoveAt(miUsedElements - 1);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::ByteSize(void)
{
	return miUsedElements * sizeof(M);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
BOOL CArrayTemplateMinimal<M>::SetArraySize(int iNum)
{
	if (miUsedElements != iNum)
	{
		return Reallocate(iNum);
	}
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
M* CArrayTemplateMinimal<M>::SetArraySize(int iNum, int iClearValue)
{
	int		iOldUsed;
	void*	pvClearStart;
	int		iClearSize;
	BOOL	bResult;

	if (miUsedElements != iNum)
	{
		iOldUsed = -1;
		if (iNum > miUsedElements)
		{
			iOldUsed = miUsedElements;
		}
		bResult = Reallocate(iNum);

		if (!bResult)
		{
			return NULL;
		}

		if (iOldUsed != -1)
		{
			pvClearStart = (void*)((ENGINE_SIZE_T) ((int)((ENGINE_SIZE_T) mpvArray) + (iOldUsed * sizeof(M))));
			iClearSize = (miUsedElements - iOldUsed) * sizeof(M);
			memset(pvClearStart, iClearValue, iClearSize);
			return (M*)pvClearStart;
		}
	}

	//No new elements were added.
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::NumElements(void)
{
	return miUsedElements;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::Copy(CArrayTemplateMinimal* pArray)
{
	Kill();
	SetArraySize(pArray->NumElements());
	memcpy(mpvArray, pArray->mpvArray, miUsedElements * sizeof(M));
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::Zero(void)
{
	if (miUsedElements != 0)
	{
		memset(mpvArray, 0, miUsedElements * sizeof(M));
	}
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::Zero(int iStart, int iEnd)
{
	if ((iStart > 0) && (iEnd <= miUsedElements))
	{
		memset((void*)Get(iStart), 0, (iEnd-iStart) * sizeof(M));
	}
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::QuickSort(int(* Func)(const void*, const void*))
{
	qsort((void*)mpvArray, miUsedElements, sizeof(M), Func);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::InsertIntoSorted(int(* Func)(const void*, const void*), M* pvElement)
{
	int	iPos;

	iPos = FindInSorted(pvElement, Func, 1);
	if (iPos < miUsedElements)
	{
		InsertAt(pvElement, iPos);
	}
	else
	{
		Add(pvElement);
	}
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::FindInSorted(M* pData, int(* Func)(const void*, const void*), int bFindIfNone)
{
	if (miUsedElements == 0)
	{
		if (bFindIfNone)
		{
			return 0;
		}
		return -1;
	}
	return BinarySearch(pData, 0, miUsedElements - 1, Func, bFindIfNone);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::BinarySearch(M* pData, int iLeft, int iRight, int(* Func)(const void*, const void*), int bFindIfNone)
{
	int		iMiddle;
	int		iResultMiddle;

	iResultMiddle = 0;
	while (iLeft <= iRight)
	{
		iMiddle = (iLeft + iRight) >> 1; //Divide by 2
		iResultMiddle = Func(pData, Get(iMiddle));
		if (iResultMiddle == 0)
		{
			return iMiddle;
		}
		else if (iResultMiddle < 0)
		{
			iRight = iMiddle - 1;
		}
		else
		{
			iLeft = iMiddle + 1;
		}
	}

	if (bFindIfNone)
	{
		if (iResultMiddle > 0)
		{
			return iMiddle + 1;
		}
		return iMiddle;
	}
	return -1;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
M* CArrayTemplateMinimal<M>::InsertAt(int iElementPos)
{
	M* ptr;

	//Grow the array.
	Add();

	//This assumes that iElementPos is within the array (or the last element).
	ptr = (M*)((ENGINE_SIZE_T) mpvArray + iElementPos * sizeof(M));
	memmove((M*)((ENGINE_SIZE_T) ptr + sizeof(M)), ptr, sizeof(M) * (miUsedElements - 1 - iElementPos));
	return ptr;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::InsertAt(M* pvData, int iElementPos)
{
	M* ptr;

	ptr = InsertAt(iElementPos);
	memcpy(ptr, pvData, sizeof(M));
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::Find(M* pData)
{
	int		i;
	M*	pPos;

	pPos = mpvArray;

	for (i = 0; i < miUsedElements; i++)
	{
		if (memcmp(pPos, pData, sizeof(M)) == 0)
		{
			return i;
		}
		pPos = (M*)((ENGINE_SIZE_T) pPos + sizeof(M));
	}
	return -1;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::FindWithKey(M* pData, int iKeyOffset, int iKeySize)
{
	int		i;
	M*	pPos;

	pPos = mpvArray;

	for (i = 0; i < miUsedElements; i++)
	{
		if (memcmp((M*)((ENGINE_SIZE_T) pPos + iKeyOffset), (M*)((ENGINE_SIZE_T) pData + iKeyOffset), iKeySize) == 0)
		{
			return i;
		}
		pPos = (M*)((ENGINE_SIZE_T) pPos + sizeof(M));
	}
	return -1;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int	CArrayTemplateMinimal<M>::FindWithIntKey(int iKey, int iKeyOffset)
{
	int		i;
	void*	pPos;

	pPos = (void*)((ENGINE_SIZE_T) ((int)((ENGINE_SIZE_T) mpvArray) + iKeyOffset));
	for (i = 0; i < miUsedElements; i++)
	{
		if (*((int*)pPos) == iKey)
		{
			return i;
		}
		pPos = RemapSinglePointer(pPos, sizeof(M));
	}
	return -1;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::AddIfUnique(M* pData)
{
	int iElementNum;

	iElementNum = Find(pData);
	if (iElementNum == -1)
	{
		Add(pData);
	}
	return iElementNum;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::AddIfUniqueKey(M* pData, int iKeyOffset, int iKeySize)
{
	int	iElementNum;

	iElementNum = FindWithKey(pData, iKeyOffset, iKeySize);
	if (iElementNum == -1)
	{
		Add(pData);
		iElementNum = miUsedElements - 1;
	}
	return iElementNum;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::GetAdjustedIndex(int iIndex)
{
	if (iIndex == -1)
	{
		return NumElements()-1;
	}
	return iIndex;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::GetIndex(M* pvElement)
{
	int iPosition;
	int iBase;
	int iDifference;

	iBase = (int)(ENGINE_SIZE_T) mpvArray;
	iPosition = (int)(ENGINE_SIZE_T) pvElement;
	iDifference = iPosition - iBase;

	//Make sure the element is correctly aligned.
	if (iDifference % sizeof(M) != 0)
	{
		return -1;
	}

	//Make sure the element lies within the array.
	iPosition = iDifference / sizeof(M);
	if ((iPosition < 0) || (iPosition >= miUsedElements))
	{
		return -1;
	}

	return iPosition;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::Set(int iElementPos, M* pvData)
{
	M*	pvTemp;

	pvTemp = Get(iElementPos);
	memcpy((M*)((ENGINE_SIZE_T) mpvArray + (iElementPos) * sizeof(M)), pvData, sizeof(M));
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::GrowToNumElements(int iNumElements)
{
	int	iOldUsedElments;

	iOldUsedElments = miUsedElements;
	SetArraySize(iNumElements);
	return iOldUsedElments;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
int CArrayTemplateMinimal<M>::GrowByNumElements(int iNumElements)
{
	int	iOldUsedElments;

	iOldUsedElments = miUsedElements;
	SetArraySize(miUsedElements + iNumElements);
	return iOldUsedElments;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
M* CArrayTemplateMinimal<M>::InsertNumElementsAt(int iNumElements, int iElementPos)
{
	M*		pvNew;
	M*		pvFrom;
	M*		pvTo;
	int		iNumToMove;

	if (iNumElements <= 0)
	{
		return NULL;
	}

	pvNew = (M*)Malloc((miUsedElements + iNumElements) * sizeof(M));

	if (iElementPos > 0)
	{
		memcpy(pvNew, mpvArray, iElementPos * sizeof(M));
	}

	iNumToMove = miUsedElements - iElementPos;
	pvFrom = Get(iElementPos);
	pvTo = &pvNew[iElementPos + iNumElements];
	memcpy(pvTo, pvFrom, iNumToMove * sizeof(M));

	Free(mpvArray);
	mpvArray = pvNew;

	return (M*)pvFrom;
}



//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
M* CArrayTemplateMinimal<M>::Tail(void)
{
	if (miUsedElements == 0)
	{
		return NULL;
	}
	return Get(miUsedElements-1);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
M* CArrayTemplateMinimal<M>::GetData(void)
{
	return mpvArray;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::FakeSetUsedElements(int iUsedElements)
{
	this->miUsedElements = iUsedElements;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::BatchRemoveElements(int iFirstElementPos, int iNumInBatch, int iNumBatches, int iStrideToNextBatch)
{
	int		i;
	M*		pcFirst;
	int		iTotalStride;
	M*		pcSource;
	M*		pcDest;
	int		iDestPos;
	int		iSourcePos;
	int		iRemaining;

	iTotalStride = iStrideToNextBatch;
	iStrideToNextBatch = iStrideToNextBatch - iNumInBatch;
	pcFirst = Get(iFirstElementPos);

	for (i = 0; i <= iNumBatches-2; i++)
	{
		memcpy(RemapSinglePointer(pcFirst, iStrideToNextBatch * i), RemapSinglePointer(pcFirst, iTotalStride * (i+1) - iStrideToNextBatch), iStrideToNextBatch);
	}

	i = iNumBatches-1;

	iDestPos = iTotalStride * (i+1) - iStrideToNextBatch;
	iSourcePos = iStrideToNextBatch * i;
	pcDest = (M*)RemapSinglePointer(pcFirst, iDestPos);
	pcSource = (M*)RemapSinglePointer(pcFirst, iSourcePos);

	iRemaining = (miUsedElements - iDestPos) - iFirstElementPos;

	if (iRemaining > 0)
	{
		memcpy(pcSource, pcDest, iRemaining);
	}

	GrowToNumElements(miUsedElements - iNumInBatch * iNumBatches);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::BatchInsertElements(int iFirstElementPos, int iNumInBatch, int iNumBatches, int iStrideToNextBatch)
{
	int		i;
	M*		pcFirst;
	int		iTotalStride;
	M*		pcSource;
	M*		pcDest;
	int		iDestPos;
	int		iSourcePos;
	int		iOldNumElements;
	int		iRemaining;

	iOldNumElements = GrowByNumElements(iNumInBatch * iNumBatches);

	iTotalStride = iNumInBatch + iStrideToNextBatch;
	pcFirst = Get(iFirstElementPos);

	i = iNumBatches-1;

	iDestPos = iTotalStride * (i+1) - iStrideToNextBatch;
	iSourcePos = iStrideToNextBatch * i;
	pcDest = (M*)RemapSinglePointer(pcFirst, iDestPos);
	pcSource = (M*)RemapSinglePointer(pcFirst, iSourcePos);

	iRemaining = (iOldNumElements - iSourcePos) - iFirstElementPos;

	if (iRemaining > 0)
	{
		memcpy(pcDest, pcSource, iRemaining);
	}

	if (iStrideToNextBatch == 1)
	{
		for (i = iNumBatches-2; i >= 0; i--)
		{
			memcpy_fast_1byte(RemapSinglePointer(pcFirst, iTotalStride * (i+1) - iStrideToNextBatch), RemapSinglePointer(pcFirst, iStrideToNextBatch * i));
		}
	}
	else if (iStrideToNextBatch == 2)
	{
		for (i = iNumBatches-2; i >= 0; i--)
		{
			memcpy_fast_2bytes(RemapSinglePointer(pcFirst, iTotalStride * (i+1) - iStrideToNextBatch), RemapSinglePointer(pcFirst, iStrideToNextBatch * i));
		}
	}
	else if (iStrideToNextBatch == 4)
	{
		for (i = iNumBatches-2; i >= 0; i--)
		{
			memcpy_fast_4bytes(RemapSinglePointer(pcFirst, iTotalStride * (i+1) - iStrideToNextBatch), RemapSinglePointer(pcFirst, iStrideToNextBatch * i));
		}
	}
	else if (iStrideToNextBatch == 8)
	{
		for (i = iNumBatches-2; i >= 0; i--)
		{
			memcpy_fast_8bytes(RemapSinglePointer(pcFirst, iTotalStride * (i+1) - iStrideToNextBatch), RemapSinglePointer(pcFirst, iStrideToNextBatch * i));
		}
	}
	else if (iStrideToNextBatch == 12)
	{
		for (i = iNumBatches-2; i >= 0; i--)
		{
			memcpy_fast_12bytes(RemapSinglePointer(pcFirst, iTotalStride * (i+1) - iStrideToNextBatch), RemapSinglePointer(pcFirst, iStrideToNextBatch * i));
		}
	}
	else
	{
		for (i = iNumBatches-2; i >= 0; i--)
		{
			memcpy(RemapSinglePointer(pcFirst, iTotalStride * (i+1) - iStrideToNextBatch), RemapSinglePointer(pcFirst, iStrideToNextBatch * i), iStrideToNextBatch);
		}
	}	
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void* CArrayTemplateMinimal<M>::Malloc(size_t tSize)
{
	return malloc(tSize);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void CArrayTemplateMinimal<M>::Free(void* pv)
{
	free(pv);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
void* CArrayTemplateMinimal<M>::Realloc(void* pv, size_t tSize)
{
	pv = realloc(pv, tSize);
	return pv;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
BOOL CArrayTemplateMinimal<M>::Write(CFileWriter* pcFileWriter)
{
	if (!pcFileWriter->WriteInt(miUsedElements))
	{ 
		return FALSE; 
	}

	if (miUsedElements != 0)
	{
		if (!pcFileWriter->WriteData(mpvArray, ByteSize())) 
		{ 
			return FALSE; 
		}
	}
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
template<class M>
BOOL CArrayTemplateMinimal<M>::Read(CFileReader* pcFileReader)
{
	int		iUsedElements;

	if (!pcFileReader->ReadInt(&iUsedElements))
	{
		return FALSE; 
	}
	mpvArray = NULL;
	miUsedElements = 0;

	if (iUsedElements != 0)
	{
		if (!Reallocate(iUsedElements))
		{
			return FALSE;
		}

		if (!pcFileReader->ReadData(mpvArray, ByteSize())) 
		{ 
			return FALSE; 
		}
	}
	return TRUE;
}


#endif // __ARRAY_TEMPLATE_MINIMAL_H__

