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
#ifndef __OBJET_SERIALISER_H__
#define __OBJET_SERIALISER_H__
#include "BaseLib/FileWriter.h"
#include "BaseLib/MemoryFile.h"
#include "BaseObject.h"
#include "PointerObject.h"


class CObjectSerialiser : public CFileWriter
{
protected:
	CBaseObject*			mpcThis;
	CMemoryFile*			mpcMemory;
	CFileBasic				mcFile;

public:
			void			Init(CBaseObject* pcObject);
	virtual void			Kill(void);
			BOOL			Save(void);

	virtual BOOL			WritePointer(CPointerObject pObject);
			BOOL			WriteHeader(CBaseObject* pcBaseObject);
	virtual BOOL			WriteDependent(CBaseObject* pcBaseObject);

			void*			GetData(void);
			int				GetLength(void);

protected:
			filePos			Write(const void* pvSource, filePos iSize, filePos iCount);
};


#endif // __OBJET_SERIALISER_H__
