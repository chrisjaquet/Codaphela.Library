#include "BaseLib/DiskFile.h"
#include "ObjectReaderSimple.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CObjectReaderSimple::Init(CFileBasic* pcFile)
{
	mpcFile = pcFile;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CObjectReaderSimple::Kill(void)
{
	mpcFile = NULL;
	CObjectReader::Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CSerialisedObject* CObjectReaderSimple::Read(char* szObjectName)
{
	CSerialisedObject*	pcSerialised;
	CChars				szDirectory;
	CChars				szFileName;
	char				szExtension[4];
	BOOL				bResult;
	int					iFileType;

	szFileName.Kill();
	szDirectory.Kill();

	bResult = mpcFile->Open(EFM_Read);
	if (!bResult)
	{
		return NULL;
	}
	
	//Write file type identifier.
	bResult = mpcFile->ReadData(szExtension, 4);
	if ((!bResult) || (strcmp(szExtension, OBJECT_FILE_EXTENSION) != 0))
	{
		return NULL;
	}

	bResult = mpcFile->ReadInt(&iFileType);
	if ((!bResult) || (iFileType != BASIC_OBJECT_FILE))
	{
		return NULL;
	}

	pcSerialised = ReadSerialised(mpcFile);
	if (!pcSerialised)
	{
		return NULL;
	}

	mpcFile->Close();
	return pcSerialised;
}


