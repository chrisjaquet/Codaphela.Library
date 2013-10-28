#include "ChunkFileHeader.h"


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void CChunkFileHeader::WriteInit(int iUserID)
{
	this->iUserID = iUserID;
	iChunkNamesPos = -1;
	memset(acMD5Hash, 0, 16);
	iMagic = CHUNK_HEADER_MAGIC;
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void CChunkHeader::WriteInit(void)
{
	iChunkIndexPos = -1;
	iChunkSize = 0;
	iName = -1;
	memset(acMD5Hash, 0, 16);
	iMagic = CHUNK_HEADER_MAGIC;
}
