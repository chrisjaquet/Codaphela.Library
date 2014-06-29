/** ---------------- COPYRIGHT NOTICE, DISCLAIMER, and LICENSE ------------- **

Copyright (c) 2012 Andrew Paterson

This file is part of The Codaphela Project: Codaphela InputLib

Codaphela InputLib is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Codaphela InputLib is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Codaphela InputLib.  If not, see <http://www.gnu.org/licenses/>.

Microsoft Windows is Copyright Microsoft Corporation

** ------------------------------------------------------------------------ **/
#ifndef __INPUT_VIRTUAL_DEVICE_COMMONALITY_H__
#define __INPUT_VIRTUAL_DEVICE_COMMONALITY_H__
#include "BaseLib/ArraySimple.h"


class CInputVirtualDevice;
class CInputVirtualDeviceCommonality : public CUnknown
{
BASE_FUNCTIONS(CInputVirtualDeviceCommonality);
protected:
	CInputVirtualDevice*				mpcVirtualDevice;
	CArraySimple<CInputVirtualDevice*>	mapcSharedDeviceSources;

public:
	void Init(CInputVirtualDevice* pcVirtualDevice);
	void Kill(void);
	void ToString(CChars* psz);

	void Clear(void);
	void Sort(void);
	void AddIfShared(CInputVirtualDevice* pcOtherVirtualDevice);
	void Disable(void);
	void Dump(void);
};


#endif // __INPUT_VIRTUAL_DEVICE_COMMONALITY_H__

