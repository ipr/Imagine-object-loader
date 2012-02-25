//
// CIobReader : read&process Imagine object data
//
// Ilkka Prusi 2012
//

#ifndef IOBREADER_H
#define IOBREADER_H

// use ISO-standard typedefs when available
#include <stdint.h>

#include "IobTags.h" // LWO tag-ID definitions

#include "AnsiFile.h"


#ifndef BYTE
typedef uint8_t  BYTE;
#endif

// object node for handling/containing object data
class IobNode;
class IobNode
{
public:
	IobNode() {};

	// siblings in tree-like hierarchy
	IobNode *left;
	IobNode *right;
	IobNode *child;

	// dbl-linking "flat" order
	IobNode *next;
	IobNode *prev;

};

class CIobReader
{
private:
	// size of file according to file header:
	// actual size - 8 bytes (IFF FORM tag and size field)
	uint32_t m_size;

	// amount read so far..
	uint32_t m_read;

protected:

	// tag-ID from data/string
	// (e.g. "FORM")
	inline unsigned int MakeTag(const char *buf);

	// byteswap bigendian<->little-endian
	// (2 bytes)
	inline unsigned short BSwap2s(const unsigned short *buf);

	// byteswap bigendian<->little-endian
	// (4 bytes)
	inline unsigned int BSwap4i(const unsigned int *buf);

	// byteswap for float:
	// avoid int<->float cast during byteswap to avoid rounding errors
	inline float BSwapF(const float fVal);

	// handle data in chunk (if supported)
	bool handleChunk(CIOBuffer &buffer, unsigned int chunkID, unsigned int chunkSize);

	// read&handle each chunk in file (if supported)
	bool readChunks(CAnsiFile &file, CIOBuffer &buffer);

public:
    CIobReader();

	bool readFile(CAnsiFile &file);
};

#endif // IOBREADER_H
