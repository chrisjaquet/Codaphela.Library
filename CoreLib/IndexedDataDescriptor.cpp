/** ---------------- COPYRIGHT NOTICE, DISCLAIMER, and LICENSE ------------- **

Copyright (c) 2009 Andrew Paterson

This file is part of The Codaphela Project: Codaphela CoreLib

Codaphela CoreLib is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Codaphela CoreLib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Codaphela CoreLib.  If not, see <http://www.gnu.org/licenses/>.

Microsoft Windows is Copyright Microsoft Corporation

** ------------------------------------------------------------------------ **/
#include "IndexedDataDescriptor.h"
#include "BaseLib/IntegerHelper.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexedDataDescriptor::Init(OIndex oi, unsigned int uiDataSize)
{
	moi = oi;

	muiDataSize = uiDataSize;
	msFlags = 0;

	miFileIndex = -1;
	miIndexInFile = -1;

	mpvCache = NULL;
	muiTimeStamp = 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexedDataDescriptor::IsAllocated(void)
{
	return muiDataSize != 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexedDataDescriptor::IsDirty(void)
{
	return msFlags & INDEXED_DESCRIPTOR_DIRTY;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexedDataDescriptor::Dirty(BOOL bDirty)
{
	if (bDirty)
	{
		msFlags |= INDEXED_DESCRIPTOR_DIRTY;
	}
	else
	{
		msFlags &= ~INDEXED_DESCRIPTOR_DIRTY;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexedDataDescriptor::SetUserFlags(int iFlags)
{
	if (iFlags & INDEXED_DESCRIPTOR_DIRTY)
	{
		return FALSE;
	}
	msFlags = (msFlags & INDEXED_DESCRIPTOR_DIRTY) | iFlags;
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexedDataDescriptor::GetUserFlags(void)
{
	return msFlags & ~INDEXED_DESCRIPTOR_DIRTY;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
unsigned int CIndexedDataDescriptor::GetDataSize(void)
{
	return muiDataSize;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexedDataDescriptor::Cache(void* pvCache)
{
	mpvCache = pvCache;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
OIndex CIndexedDataDescriptor::GetIndex(void)
{
	return moi;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexedDataDescriptor::HasFile(void)
{
	return miFileIndex != -1;
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexedDataDescriptor::IsCached(void)
{
	return FixBool(mpvCache);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* CIndexedDataDescriptor::GetCache(void)
{
	return mpvCache;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexedDataDescriptor::TimeStamp(unsigned int uiTimeStamp)
{
	muiTimeStamp = uiTimeStamp;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexedDataDescriptor::SetIndexes(int iFileIndex, filePos iIndexInFile)
{
	miFileIndex = iFileIndex;
	miIndexInFile = iIndexInFile;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexedDataDescriptor::GetFileIndex(void)
{
	return miFileIndex;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
filePos CIndexedDataDescriptor::GetIndexInFile(void)
{
	return miIndexInFile;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
unsigned int CIndexedDataDescriptor::GetTimeStamp(void)
{
	return muiTimeStamp;
}

