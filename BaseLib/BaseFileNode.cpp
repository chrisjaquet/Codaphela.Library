#include "BaseFileNode.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CBaseFileNode::Init(char* szName, EFileNodeType eType, CBaseFileNode* pcParent)
{
	meType = eType;
	mszName.Init(szName);
	mpcParent = pcParent;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CBaseFileNode::Kill(void)
{
	mszName.Kill();
	meType = FNT_Unknown;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CBaseFileNode::GetName(void)
{
	return mszName.Text();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CBaseFileNode::GetFullName(CChars* pszDest)
{
	CBaseFileNode*	pcCurrent;
	CChars			szName;

	szName.Init();

	pcCurrent = this;
	while (pcCurrent)
	{
		szName.Insert(0, pcCurrent->GetName());
		pcCurrent = pcCurrent->GetParent();
		szName.Insert(0, "/");
	}
	szName.RemoveFromStart(2);

	pszDest->Append(szName);
	szName.Kill();
	return pszDest->Text();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CBaseFileNode::Is(char* szName)
{
	return mszName.Equals(szName);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CBaseFileNode::IsDirectory(void)
{
	return meType == FNT_Directory;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CBaseFileNode::IsFile(void)
{
	return meType == FNT_File;
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CBaseFileNode* CBaseFileNode::GetParent(void)
{
	return mpcParent;
}
