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
#include "OperatorRemainder.h"
#include "BaseLib/GeometricTypes.h"

void RemainderInvalid(void* pvDest, void* pvLeft, void* pvRight) { gcUserError.Set("Remainder not defined for types"); }
#include "OperatorRemainder_Functions.inl"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void COperatorRemainder::Init(void)
{
	int		iDest;
	int		iLeft;
	int		iRight;

	for (iDest = 0; iDest < PRIMTIVE_OPERATOR_END; iDest++)
	{
		for (iLeft = 0; iLeft < PRIMTIVE_OPERATOR_END; iLeft++)
		{
			for (iRight = 0; iRight < PRIMTIVE_OPERATOR_END; iRight++)
			{
				mapvRemainder[iDest][iLeft][iRight] = RemainderInvalid;
			}
		}
	}
#include "OperatorRemainder_Mapping.inl"
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void COperatorRemainder::Kill(void)
{
	//Does Nothing...
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void COperatorRemainder::Do(EPrimitiveTypes eDest, void* pvDest, EPrimitiveTypes eLeft, void* pvLeft, EPrimitiveTypes eRight, void* pvRight)
{
	mapvRemainder[eDest][eLeft][eRight](pvDest, pvLeft, pvRight);
}
