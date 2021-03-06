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
#include "ConstructorCall.h"
#include "Chars.h"
#include "MD5HashFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMD5HashFile::Init(CAbstractFile*	pcFile)
{
	CAbstractFile::Init();
	mbHashing = FALSE;
	MD5Init(&msMD5Context);
	mpcFile = pcFile;
	mbResetMD5OnSeek = TRUE;
	mbResetMD5OnOperationChange = TRUE;
	meLastOp = LMD5OP_None;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMD5HashFile::Kill(void)
{
	mpcFile->Kill();
	if (mpcFile->mbBasicFileMustFree)
	{
		free(mpcFile);
		mpcFile = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CMD5HashFile::Open(EFileMode eFileMode)
{
	BOOL	bResult;

	bResult = mpcFile->Open(eFileMode);
	if (bResult)
	{
		StartHashing();
	}
	else
	{
		mbHashing = FALSE;
	}
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CMD5HashFile::Close()
{
	BOOL	iResult;

	StopHashing();
	iResult = mpcFile->Close();
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMD5HashFile::StopHashing(void)
{
	if (IsOpen())
	{
		if (mbHashing)
		{
			MD5Final(&msMD5Context);
			mbHashing = FALSE;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMD5HashFile::StartHashing(void)
{
	if (IsOpen())
	{
		MD5Init(&msMD5Context);
		mbHashing = TRUE;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CMD5HashFile::IsOpen(void)
{
	return mpcFile->IsOpen();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
filePos CMD5HashFile::Read(void* pvBuffer, filePos iSize, filePos iCount)
{
	filePos		iSuccessfulCount;
	filePos		iSuccessfulBytes;

	if (mbResetMD5OnOperationChange)
	{
		if (meLastOp != LMD5OP_Read)
		{
			StartHashing();
		}
	}
	meLastOp = LMD5OP_Read;

	iSuccessfulCount = mpcFile->Read(pvBuffer, iSize, iCount);
	if (iSuccessfulCount > 0)
	{
		iSuccessfulBytes = iSuccessfulCount * iSize;
		MD5Update(&msMD5Context, (unsigned char*)pvBuffer, (unsigned int)iSuccessfulBytes);
	}
	return iSuccessfulCount;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
filePos CMD5HashFile::Write(const void* pvBuffer, filePos iSize, filePos iCount)
{
	filePos		iSuccessfulCount;
	filePos		iSuccessfulBytes;

	if (mbResetMD5OnOperationChange)
	{
		if (meLastOp != LMD5OP_Write)
		{
			StartHashing();
		}
	}
	meLastOp = LMD5OP_Write;

	iSuccessfulCount = mpcFile->Write(pvBuffer, iSize, iCount);
	if (iSuccessfulCount > 0)
	{
		iSuccessfulBytes = iSuccessfulCount * iSize;
		MD5Update(&msMD5Context, (unsigned char*)pvBuffer, (unsigned int)iSuccessfulBytes);
	}
	return iSuccessfulCount;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CMD5HashFile::Seek(filePos iOffset, EFileSeekOrigin iSeekOrigin)
{
	if (mbResetMD5OnSeek)
	{
		StartHashing();
	}
	return mpcFile->Seek(iOffset, iSeekOrigin);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
filePos CMD5HashFile::Tell(void)
{
	return mpcFile->Tell();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CMD5HashFile::Eof(void)
{
	return mpcFile->Eof();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
filePos CMD5HashFile::Size(void)
{
	return mpcFile->Size();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CMD5HashFile::Flush(void)
{
	return mpcFile->Flush();
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
BOOL CMD5HashFile::Delete(void)
{
	if (IsOpen())
	{
		return FALSE;
	}

	return mpcFile->Delete();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMD5HashFile::ResetHash(void)
{
	StartHashing();
	meLastOp = LMD5OP_None;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMD5HashFile::CopyContextToDest(SMD5Context* psDestContext)
{
	memcpy(psDestContext, &msMD5Context, sizeof(SMD5Context));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMD5HashFile::CopyContextFromSource(SMD5Context* psSourceContext)
{
	memcpy(&msMD5Context, psSourceContext, sizeof(SMD5Context));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMD5HashFile::CopyDigestToDest(void* pvDest)
{
	memcpy(pvDest, msMD5Context.digest, 16);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMD5HashFile::Dump(void)
{
	CChars	sz;

	sz.Init();
	sz.AppendHexLoHi(msMD5Context.digest, 16);
	sz.AppendNewLine();
	sz.Dump();
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CMD5HashFile* MD5HashFile(CAbstractFile* pcFile)
{
	CMD5HashFile* pcHashFile;

	pcHashFile = NewMalloc<CMD5HashFile>();
	pcHashFile->Init(pcFile);
	pcHashFile->mbBasicFileMustFree = TRUE;
	return pcHashFile;
}

