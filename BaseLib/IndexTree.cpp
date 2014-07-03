#include "Numbers.h"
#include "IndexTree.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTree::Init(void)
{
	mpcRoot = AllocateRoot();
	miSize = 0;
	miModifications = 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTree::Kill(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTree::RecurseKill(CIndexTreeNode* pcNode)
{
	int					i;
	CIndexTreeNode*		pcChild;

	if (pcNode != NULL)
	{
		for (i = 0; i < pcNode->GetNumIndexes(); i++)
		{
			pcChild = pcNode->GetNode(i);
			RecurseKill(pcChild);
		}
		FreeNode(pcNode);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* CIndexTree::Malloc(size_t tSize)
{
	return malloc(tSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTree::Free(void* pv)
{
	free(pv);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* CIndexTree::Realloc(void* pv, size_t tSize)
{
	void* pvNew;

	pvNew = realloc(pv, tSize);
	return pvNew;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode* CIndexTree::AllocateNode(CIndexTreeNode* pcParent)
{
	CIndexTreeNode*	pcNode;

	pcNode = (CIndexTreeNode*)Malloc(sizeof(CIndexTreeNode));
	pcNode->Init(pcParent);
	return pcNode;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode* CIndexTree::AllocateRoot(void)
{
	CIndexTreeNode*		pcNode;
	int					iAdditionalSize;

	iAdditionalSize = MAX_UCHAR * sizeof(CIndexTreeNode*);
	pcNode = (CIndexTreeNode*)Malloc(sizeof(CIndexTreeNode) + iAdditionalSize);
	pcNode->Init(NULL, 0, MAX_UCHAR);
	return pcNode;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode* CIndexTree::ReallocateNodeForIndex(CIndexTreeNode* pcNode, unsigned char uiIndex)
{
	CIndexTreeNode*		pcOldNode;
	CIndexTreeNode*		pcParent;
	size_t				tNewNodeSize;

	if (pcNode->ContainsIndex(uiIndex))
	{
		return pcNode;
	}

	if (pcNode->HasNodes())
	{
		tNewNodeSize = pcNode->CalculateRequiredNodeSizeForIndex(uiIndex);
	}
	else
	{
		tNewNodeSize = pcNode->CalculateRequiredNodeSizeForEmpty();
	}

	pcOldNode = pcNode;
	pcNode = (CIndexTreeNode*)Realloc(pcNode, tNewNodeSize);
	pcNode->Contain(uiIndex);

	if (pcOldNode != pcNode)
	{
		pcParent = pcNode->GetParent();
		if (pcParent)
		{
			pcParent->RemapChildNodes(pcOldNode, pcNode);
		}
	}

	return pcNode;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode* CIndexTree::ReallocateNodeForData(CIndexTreeNode* pcNode, unsigned char uiDataSize)
{
	CIndexTreeNode*		pcOldNode;
	CIndexTreeNode*		pcParent;
	size_t				tNewNodeSize;

	tNewNodeSize = pcNode->CalculateRequiredNodeSizeForData(uiDataSize);

	pcOldNode = pcNode;
	pcNode = (CIndexTreeNode*)Realloc(pcNode, tNewNodeSize);

	if (pcOldNode != pcNode)
	{
		pcParent = pcNode->GetParent();
		if (pcParent)
		{
			pcParent->RemapChildNodes(pcOldNode, pcNode);
		}
	}

	return pcNode;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTree::FreeNode(CIndexTreeNode* pcNode)
{
	Free(pcNode);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode* CIndexTree::GetIndexNode(char* pszKey)
{
	CIndexTreeNode* pcCurrent;
	int				iKeySize;

	if (StrEmpty(pszKey))
	{
		return NULL;
	}

	iKeySize = strlen(pszKey);

	pcCurrent = mpcRoot;
	for (int i = 0; i < iKeySize; i++)
	{
		char c = pszKey[i];

		pcCurrent = pcCurrent->Get(c);
		if (pcCurrent == NULL)
		{
			return NULL;
		}
	}
	return pcCurrent;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* CIndexTree::Get(char* pszKey)
{
	CIndexTreeNode* pcNode;
	void*			pv;

	if (StrEmpty(pszKey))
	{
		return NULL;
	}

	pcNode = GetIndexNode(pszKey);
	if (pcNode == NULL)
	{
		return NULL;
	}
	else
	{
		if (pcNode->GetObjectSize() == 0)
		{
			return NULL;
		}
		pv = pcNode->GetObjectPtr();
		return pv;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTree::Put(void* pvObject, unsigned char uiObjectSize, char* pszKey)
{
	int					iKeySize;
	CIndexTreeNode*		pcCurrent;
	CIndexTreeNode*		pcReallocatedCurrent;
	unsigned char		c;
	BOOL				bResult;

	if (StrEmpty(pszKey))
	{
		return FALSE;
	}

	iKeySize = strlen(pszKey);
	pcCurrent = mpcRoot;

	for (int i = 0; i < iKeySize; i++)
	{
		c = pszKey[i];
		pcCurrent = SetOldWithCurrent(pcCurrent, c);
	}

	miModifications++;
	miSize++;
	
	pcReallocatedCurrent = ReallocateNodeForData(pcCurrent, uiObjectSize);
	bResult = pcReallocatedCurrent->SetObject(&pvObject, uiObjectSize);
	if (pcCurrent != pcReallocatedCurrent)
	{
		pcReallocatedCurrent->SetChildsParent();
	}
	return bResult;
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTree::Add(char* pszKey, void* pvObject, unsigned char uiObjectSize)
{
	return Put(pvObject, uiObjectSize, pszKey);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode* CIndexTree::SetOldWithCurrent(CIndexTreeNode* pcParent, unsigned char c)
{
	CIndexTreeNode* pcNew;
	CIndexTreeNode* pcCurrent;
	CIndexTreeNode* pcReallocedParent;

	pcCurrent = pcParent->Get(c);
	if (pcCurrent == NULL)
	{
		pcNew = AllocateNode(pcParent);
		pcReallocedParent = ReallocateNodeForIndex(pcParent, c);
		pcReallocedParent->Set(c, pcNew);
		if (pcParent != pcReallocedParent)
		{
			pcReallocedParent->SetChildsParent();
		}
		return pcNew;
	}
	else
	{
		return pcCurrent;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void* CIndexTree::Remove(char* pszKey)
{
	char									c;
	int										iKeySize;
	CIndexTreeNode*							pcParent;
	CIndexTreeNode*							pcNode;
	CArrayEmbedded<CIndexTreeNode*, 64>		apcPath;
	CIndexTreeNode*							pcCurrent;
	void*									pvObject;

	if (pszKey == NULL)
	{
		return NULL;
	}

	apcPath.Init();
	iKeySize = strlen(pszKey);
	pcCurrent = mpcRoot;
	apcPath.Add(&pcCurrent);
	for (int i = 0; i < iKeySize; i++)
	{
		char c = pszKey[i];
		pcCurrent = pcCurrent->Get(c);
		if (pcCurrent == NULL)
		{
			return NULL;
		}
		apcPath.Add(&pcCurrent);
	}

	if (pcCurrent->GetObjectSize() == 0)
	{
		return NULL;
	}

	pvObject = ((void**) pcCurrent->GetObjectPtr());

	pcCurrent->ClearObject();
	for (int i = apcPath.NumElements() - 1; i > 0; i--)
	{
		c = pszKey[(i - 1)];
		pcNode = *apcPath.Get(i);
		pcParent = *apcPath.Get(i - 1);

		if (pcNode->IsEmpty())
		{
			pcParent->Clear(c);
		}
	}

	miModifications++;
	miSize--;
	return pvObject;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTree::FindAll(CArrayVoidPtr* papvElements)
{
	RecurseFindAll(mpcRoot, papvElements);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CIndexTree::RecurseFindAll(CIndexTreeNode* pcNode, CArrayVoidPtr* papvElements)
{
	int					i;
	CIndexTreeNode*		pcChild;
	void*				pvObject;

	if (pcNode != NULL)
	{
		pvObject = pcNode->GetObjectPtr();
		if (pvObject != NULL)
		{
			papvElements->Add(pvObject);
		}

		for (i = 0; i < pcNode->GetNumIndexes(); i++)
		{
			pcChild = pcNode->GetNode(i);
			RecurseFindAll(pcChild, papvElements);
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTree::GetSize(void)
{
	return NumElements();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTree::NumElements(void)
{
	return miSize;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTree::ValidateSize(void)
{
	int iSizeFromRecursion;

	iSizeFromRecursion = RecurseSize(mpcRoot);

	if (miSize != iSizeFromRecursion)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTree::RecurseSize(void)
{
	return RecurseSize(mpcRoot);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTree::RecurseSize(CIndexTreeNode* pcNode)
{
	int					i;
	CIndexTreeNode*		pcChild;
	unsigned char		uiSize;

	int count = 0;

	if (pcNode != NULL)
	{
		uiSize = pcNode->GetObjectSize();
		if (uiSize != 0)
		{
			count++;
		}

		for (i = 0; i < pcNode->GetNumIndexes(); i++)
		{
			pcChild = pcNode->GetNode(i);
			count += RecurseSize(pcChild);
		}
	}
	return count;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTree::Contains(char* pszKey)
{
	if (StrEmpty(pszKey))
	{
		return FALSE;
	}

	CIndexTreeNode* pcNode = GetIndexNode(pszKey);
	if (pcNode == NULL)
	{
		return FALSE;
	}

	return pcNode->GetObjectSize() != 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTree::HasKey(char* pszKey)
{
	return Contains(pszKey);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTree::CountAllocatedNodes(void)
{
	return RecurseCountAllocatedNodes(mpcRoot);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTree::RecurseCountAllocatedNodes(CIndexTreeNode* pcNode)
{
	int					i;
	CIndexTreeNode*		pcChild;

	if (pcNode != NULL)
	{
		int count = 1;
		for (i = 0; i < pcNode->GetNumIndexes(); i++)
		{
			pcChild = pcNode->GetNode(i);
			count += RecurseCountAllocatedNodes(pcChild);
		}
		return count;
	}
	else
	{
		return 0;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTree::CountListSize(void)
{
	return RecurseCountListSize(mpcRoot);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTree::RecurseCountListSize(CIndexTreeNode* pcNode)
{
	int					i;
	CIndexTreeNode*		pcChild;

	if (pcNode != NULL)
	{
		int count = pcNode->GetNumIndexes();
		for (i = 0; i < pcNode->GetNumIndexes(); i++)
		{
			pcChild = pcNode->Get(i);
			count += RecurseCountListSize(pcChild);
		}
		return count;
	}
	else
	{
		return 0;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int CIndexTree::GetModifications(void)
{
	return miModifications;
}

