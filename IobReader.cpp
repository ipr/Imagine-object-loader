//
// CIobReader : read&process Imagine object data
//
// Ilkka Prusi 2012
//

#include "IobReader.h"

// abs(), need explicit include for GCC
#include <cmath>


/////// protected methods

// make tag-ID from file
unsigned int CIobReader::MakeTag(const char *buf)
{
	return (
		(unsigned long) (buf[0])<<24
		| (unsigned long) (buf[1])<<16
		| (unsigned long) (buf[2])<<8
		| (unsigned long) (buf[3]));
}

// byteswap 2 (short)
unsigned short CIobReader::BSwap2s(const unsigned short *buf)
{
	unsigned short tmp = (*buf);
	return (((tmp >> 8)) | (tmp << 8));
}

// byteswap 4 (int)
unsigned int CIobReader::BSwap4i(const unsigned int *buf)
{
	unsigned int tmp = (*buf);
	return (
			((tmp & 0x000000FF) << 24) + ((tmp & 0x0000FF00) <<8) +
			((tmp & 0x00FF0000) >> 8) + ((tmp & 0xFF000000) >>24)
			);
}

// byteswap 4: float special case (see comments)
float CIobReader::BSwapF(const float fVal)
{
	float fTmp = fVal;

	// cast the "bit-array" via pointer for byteswap
	// so we don't make int<->float cast by mistake

	unsigned int uiTmp = BSwap4i((unsigned int*)(&fTmp));

	fTmp = (*((float*)(&uiTmp)));
	return fTmp;
}

// handle data in chunk (if supported)
bool CIobReader::handleChunk(CIOBuffer &buffer, unsigned int chunkID, unsigned int chunkSize)
{
	switch (chunkID)
	{
	case ID_INFO:
		break;

	case ID_OBJ:
		break;

		// OBJ sub-chunks
	case ID_EXTR:
	case ID_DESC:
	case ID_TOBJ:
		break;

	default:
		// unknown/unsupported chunk, just skip it
		break;
	}

	return true;
}

bool CIobReader::readChunks(CAnsiFile &file, CIOBuffer &buffer)
{
	while (m_read < m_size)
	{
		// next chunk type ID and size of it
		// in common IFF-standard style
		if (file.Read(buffer, 8) == false)
		{
			// failure
			return false;
		}
		m_read += 8;

		// next chunk
		BYTE *data = buffer.GetBegin();
		unsigned int nextID = MakeTag(data);
		unsigned int nextSize = BSwap4i(data+4);

		if (file.Read(buffer, nextSize) == false)
		{
			// failure
			return false;
		}
		m_read += nextSize;

		if (handleChunk(buffer, nextID, nextSize) == false)
		{
			// error handling?
			return false;
		}
	}

	// all done ok
	return true;
}

/////// public methods

CIobReader::CIobReader()
	: m_size(0)
	, m_read(0)
{
}

// TODO: keep read buffer somewhere outside this
// so we can reuse it for large amounts of objects
// when reading?
//
bool CIobReader::readFile(CAnsiFile &file)
{
	// for now, just keep until processed
	CIOBuffer buf(1024);
	if (file.Read(buf, 12) == false) // IFF-header
	{
		return false;
	}

	BYTE *data = buf.GetBegin();
	if (MakeTag(data) != ID_FORM)
	{
		// not standard IFF container or unsupported
		return false;
	}

	// size
	m_size = BSwap4i(data+4);

	// contained chunks: TDDD for Imagine objects
	if (MakeTag(data+8) != ID_TDDD)
	{
		return false;
	}

	// set for easy checking while reading
	m_read = 4;

	// ok, we should have supported file,
	// read chunks until done

	return readChunks(file, buf);
}

