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
#ifndef __MAP_STRING_UNKNOWN_H__
#define __MAP_STRING_UNKNOWN_H__
#include "BaseLib/MapStringTemplate.h"
#include "MapCommon.h"

class CMapStringUnknown : public CMapCommon
{
BASE_FUNCTIONS(CMapStringUnknown);
private:
	CMapStringTemplate<CUnknown*>	mcMap;

public:
	void		Init(BOOL bKillElements = TRUE, BOOL bOverwriteExisting = TRUE, int iChunkSize = MAP_COMMOM_CHUNK_SIZE);
	void		Kill(void);
	BOOL		Save(CFileWriter* pcFile);
	BOOL		Load(CFileReader* pcFile);

	template<class M>
	M*			Put(char* szKey);
	BOOL		Put(char* szKey, CUnknown* pcValue);
	CUnknown*	Get(char* szKey);
	int			NumElements(void);
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
template<class M>
M* CMapStringUnknown::Put(char* szKey)
{
	M*		pv;
	BOOL	bResult;

	if (szKey)
	{
        pv = gcUnknowns.Add<M>();
		bResult = Put(szKey, pv);
		if (bResult)
		{
			return pv;
		}
		else
		{
			//Nasty, but if we allocated (and didn't initialise) the object then it must be freed but not killed.
			gcUnknowns.RemoveInKill(pv);
			return NULL;
		}
	}
	else
	{
		//Don't try and put NULL, put the empty string "" instead.
		return NULL;
	}
}


#endif // __MAP_STRING_UNKNOWN_H__

