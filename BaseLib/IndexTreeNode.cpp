#include "PointerRemapper.h"
#include "IndexTreeNode.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTreeNode::Init(CIndexTreeNode* pcParent, unsigned char uiFirstIndex, unsigned char uiLastIndex)
{
	size_t tSize;

	muiFirstIndex = uiFirstIndex;
	muiLastIndex = uiLastIndex;
	muiDataSize = 0;
	mbNodesEmpty = FALSE;
	mpcParent = pcParent;

	tSize = (uiLastIndex - uiFirstIndex + 1) * sizeof(CIndexTreeNode*);
	memset(GetNodes(), 0, tSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTreeNode::Init(CIndexTreeNode* pcParent)
{
	mpcParent = pcParent;
	muiFirstIndex = 0;
	muiLastIndex = 0;
	muiDataSize = 0;
	mbNodesEmpty = TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTreeNode::Contain(unsigned char uiIndex)
{
	unsigned char		uiOldNumIndexes;
	void*				pvDest;
	size_t				tSize;
	CIndexTreeNode**	apcChildren;

	apcChildren = GetNodes();

	if (mbNodesEmpty == TRUE)
	{
		mbNodesEmpty = FALSE;
		muiFirstIndex = uiIndex;
		muiLastIndex = uiIndex;
		apcChildren[0] = NULL;
		return;
	}

	uiOldNumIndexes = GetNumIndexes();
	apcChildren = GetNodes();

	if (uiIndex < muiFirstIndex)
	{
		tSize = (muiFirstIndex - uiIndex) * sizeof(CIndexTreeNode*);
		pvDest = RemapSinglePointer(apcChildren, tSize);
		memcpy(pvDest, apcChildren, uiOldNumIndexes * sizeof(CIndexTreeNode*));
		memset(apcChildren, 0, tSize);
		muiFirstIndex = uiIndex;
	}
	else if (uiIndex > muiLastIndex)
	{
		tSize = (uiIndex - muiLastIndex) * sizeof(CIndexTreeNode*);
		pvDest = RemapSinglePointer(apcChildren, uiOldNumIndexes * sizeof(CIndexTreeNode*));
		memset(pvDest, 0, tSize);
		muiLastIndex = uiIndex;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode* CIndexTreeNode::Get(unsigned char uiIndex)
{
	if (ContainsIndex(uiIndex))
	{
		return GetNode(uiIndex - muiFirstIndex);
	}
	else
	{
		return NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* CIndexTreeNode::GetObjectPtr(void)
{
	if (muiDataSize == 0)
	{
		return NULL;
	}
	else
	{
		return RemapSinglePointer(this, sizeof(CIndexTreeNode));
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
unsigned char CIndexTreeNode::GetObjectSize(void)
{
	return muiDataSize;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTreeNode::Set(unsigned char uiIndex, CIndexTreeNode* pcNode)
{
	CIndexTreeNode**	apcChildren;

	if (ContainsIndex(uiIndex))
	{
		apcChildren = GetNodes();
		apcChildren[uiIndex - muiFirstIndex] = pcNode;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTreeNode::Clear(unsigned char uiIndex)
{
	CIndexTreeNode**	apcChildren;

	if (ContainsIndex(uiIndex))
	{
		apcChildren = GetNodes();
		apcChildren[uiIndex - muiFirstIndex] = NULL;
	}
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTreeNode::SetObject(void* pvObject, unsigned char uiSize)
{
	if (muiDataSize == 0)
	{
		SizeObject(uiSize);
		memcpy(GetObjectPtr(), pvObject, uiSize);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTreeNode::ClearObject(void)
{
	SizeObject(0);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTreeNode::IsEmpty(void)
{
	int					i;
	CIndexTreeNode*		pcChild;
	CIndexTreeNode**	apcChildren;

	if (muiDataSize != 0)
	{
		return FALSE;
	}

	if (mbNodesEmpty == TRUE)
	{
		return TRUE;
	}

	apcChildren = GetNodes();
	for (i = 0; i <= muiLastIndex - muiFirstIndex; i++)
	{
		pcChild = apcChildren[i];
		if (pcChild != NULL)
		{
			return FALSE;
		}
	}
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
unsigned char CIndexTreeNode::GetFirstIndex(void)
{
	return muiFirstIndex;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
unsigned char CIndexTreeNode::GetLastIndex(void)
{
	return muiLastIndex;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTreeNode::HasNodes(void)
{
	return mbNodesEmpty == FALSE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTreeNode::ContainsIndex(unsigned char uiIndex)
{
	if ((uiIndex >= muiFirstIndex) && (uiIndex <= muiLastIndex))
	{
		return TRUE;
	}	
	else
	{
		return FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTreeNode::GetAdditionalIndexes(unsigned char uiIndex)
{
	unsigned char uiFirstIndex;
	unsigned char uiLastIndex;

	if (uiIndex < muiFirstIndex)
	{
		uiFirstIndex = uiIndex;
		uiLastIndex = muiLastIndex;
	}
	else if (uiIndex > muiLastIndex)
	{
		uiFirstIndex = muiFirstIndex;
		uiLastIndex = uiIndex;
	}
	else
	{
		uiFirstIndex = muiFirstIndex;
		uiLastIndex = muiLastIndex;
	}

	return ((uiLastIndex - uiFirstIndex + 1) - 1);   //+1 because uiLast is inclusive.  -1 because CIndexTreeNode already includes 1.	
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
size_t CIndexTreeNode::CalculateRequiredNodeSize(unsigned char uiIndex)
{
	size_t	tAdditionalSize;
	int		iNewIndices;

	iNewIndices = GetAdditionalIndexes(uiIndex);
	tAdditionalSize = sizeof(CIndexTreeNode) + muiDataSize + iNewIndices * sizeof(CIndexTreeNode*);

	return tAdditionalSize;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTreeNode::GetNumIndexes(void)
{
	if (mbNodesEmpty)
	{
		return 0;
	}
	return muiLastIndex - muiFirstIndex + 1;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode* CIndexTreeNode::GetNode(int i)
{
	return GetNodes()[i];
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode** CIndexTreeNode::GetNodes(void)
{
	return (CIndexTreeNode**)RemapSinglePointer(this, sizeof(CIndexTreeNode) + muiDataSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode* CIndexTreeNode::GetParent(void)
{
	return mpcParent;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTreeNode::RemapChildNodes(CIndexTreeNode* pcOldNode, CIndexTreeNode* pcNewNode)
{
	int					i;
	int					iNumNodes;
	CIndexTreeNode**	apcChildren;

	iNumNodes = GetNumIndexes();
	apcChildren = GetNodes();

	for (i = 0; i < iNumNodes; i++)
	{
		if (apcChildren[i] == pcOldNode)
		{
			apcChildren[i] = pcNewNode;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTreeNode::SetChildsParent(void)
{
	int					i;
	int					iNumNodes;
	CIndexTreeNode*		pcChild;
	CIndexTreeNode**	apcChildren;

	iNumNodes = GetNumIndexes();
	apcChildren = GetNodes();

	for (i = 0; i < iNumNodes; i++)
	{
		pcChild = apcChildren[i];
		if (pcChild)
		{
			pcChild->mpcParent = this;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTreeNode::SizeObject(unsigned char uiSize)
{
	size_t				tSize;
	CIndexTreeNode**	apcChildren;
	int					iDiff;
	CIndexTreeNode**	apcMovedChildren;

	if (!mbNodesEmpty)
	{
		apcChildren = GetNodes();
		tSize = (muiLastIndex - muiFirstIndex + 1) * sizeof(CIndexTreeNode*);

		iDiff = (int)uiSize - (int)muiDataSize;

		apcMovedChildren = (CIndexTreeNode**)RemapSinglePointer(apcChildren, iDiff);
		memmove(apcMovedChildren, apcChildren, tSize);
	}

	muiDataSize = uiSize;
}

