#include "ObjectDeserialiser.h"
#include "ObjectSerialiser.h"
#include "String.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CString::Class(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CString::Kill(void)
{
	CObject::Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CString::KillData(void)
{
	CChars::Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CString::Save(CObjectSerialiser* pcFile)
{
	return pcFile->WriteString(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CString::Load(CObjectDeserialiser* pcFile)
{
	return pcFile->ReadString(this);
}

