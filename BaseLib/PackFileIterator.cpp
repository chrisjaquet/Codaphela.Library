#include "PackFileIterator.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPackFileIterator::Init(void)
{
	mpcCurrent = NULL;
	macDepth.Init(8);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPackFileIterator::Kill(void)
{
	mpcCurrent = NULL;
	macDepth.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPackFileIterator::Push(CFileNodePackFileNode* pcNode)
{
	SPackFileIteratorPosition*	psNode;

	psNode = macDepth.Add();

	psNode->iIndex = -1;
	psNode->pcNode = pcNode;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
SPackFileIteratorPosition* CPackFileIterator::Peek(void)
{
	return macDepth.Tail();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPackFileIterator::Pop(void)
{
	macDepth.Pop();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPackFileIterator::SetCurrent(CFileNodePackFileNode* pcNode)
{
	mpcCurrent = pcNode;	
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CFileNodePackFileNode* CPackFileIterator::Current(void)
{
	return mpcCurrent;
}

