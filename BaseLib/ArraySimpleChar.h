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
#ifndef __ARRAY_SIMPLE_CHAR_H__
#define __ARRAY_SIMPLE_CHAR_H__
#include "ArraySimple.h"


//Array of simple char.
class CArraySimpleChar : public CArraySimple<char>
{
public:
	void	Init(void);
	void	Init(char* sz);
	void	Allocate(char* sz);
	void	Allocate(int iNumElements);
	void	Add(char c);
	int		AddIfUnique(char c);
	int		Find(char c);
	char	GetValue(int iElementPos);
	char*	GetArray(void);
};


#endif //__ARRAY_SIMPLE_CHAR_H__

