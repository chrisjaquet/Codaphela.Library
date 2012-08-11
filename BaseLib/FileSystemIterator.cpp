#include "FileSystemIterator.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CFileNodeIterator::Init(void)
{
	mpcCurrent = NULL;
	macDepth.Init(8);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CFileNodeIterator::Kill(void)
{
	mpcCurrent = NULL;
	macDepth.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CFileNodeIterator::Push(CSystemFileNode* pcNode)
{
	SFileSystemIteratorPosition*	psNode;

	psNode = macDepth.Add();

	psNode->iIndex = -1;
	psNode->pcNode = pcNode;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
SFileSystemIteratorPosition* CFileNodeIterator::Peek(void)
{
	return macDepth.Tail();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CFileNodeIterator::Pop(void)
{
	macDepth.Pop();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CFileNodeIterator::SetCurrent(CSystemFileNode* pcNode)
{
	mpcCurrent = pcNode;	
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CFileNodeSystemFile* CFileNodeIterator::Current(void)
{
	return mpcCurrent->File();
}