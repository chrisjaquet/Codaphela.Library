#ifndef __INDEX_TREE_NODE_H__
#define __INDEX_TREE_NODE_H__
#include "Bool.h"
#include "DataTypes.h"


class CIndexTreeNode
{
protected:
	CIndexTreeNode*		mpcParent;
	unsigned char		muiFirstIndex;
	unsigned char		muiLastIndex;
	unsigned char		muiDataSize;
	unsigned char		mbNodesEmpty;

public:
	void				Init(CIndexTreeNode* pcParent, unsigned char uiFirstIndex, unsigned char uiLastIndex);
	void				Init(CIndexTreeNode* pcParent);
	void				Contain(unsigned char uiIndex);
	CIndexTreeNode*		Get(unsigned char uiIndex);
	void*				GetObjectPtr(void);
	unsigned char		GetObjectSize(void);
	void				Set(unsigned char uiIndex, CIndexTreeNode* pcNode);
	void				Clear(unsigned char uiIndex);
	BOOL				SetObject(void* pvObject, unsigned char uiSize);
	void				ClearObject(void);
	BOOL				IsEmpty(void);
	unsigned char		GetFirstIndex(void);
	unsigned char		GetLastIndex(void);
	BOOL				HasNodes(void);
	BOOL				ContainsIndex(unsigned char uiIndex);
	int					GetAdditionalIndexes(unsigned char uiIndex);
	int					GetNumIndexes(void);
	CIndexTreeNode*		GetNode(int i);
	CIndexTreeNode*		GetParent(void);
	CIndexTreeNode**	GetNodes(void);
	void				RemapChildNodes(CIndexTreeNode* pcOldNode, CIndexTreeNode* pcNewNode);
	void				SetChildsParent(void);
	void				SizeObject(unsigned char uiSize);
	size_t				CalculateRequiredNodeSizeForIndex(unsigned char uiIndex);
	size_t				CalculateRequiredNodeSizeForEmpty(void);
	size_t				CalculateRequiredNodeSizeForData(unsigned char uiDataSize);
	unsigned char		FindPrevLastIndex(void);
	unsigned char		FindNextFirstIndex(void);
};


#endif // __INDEX_TREE_NODE_H__

