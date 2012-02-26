//
// CIobReader : read&process Imagine object data
//
// Ilkka Prusi 2012
//

#ifndef IOBREADER_H
#define IOBREADER_H

// use ISO-standard typedefs when available
#include <stdint.h>

#include "IobTags.h" // tag definitions

#include "AnsiFile.h"


#ifndef BYTE
typedef uint8_t  BYTE;
#endif
#ifndef UBYTE
typedef uint8_t  UBYTE;
#endif

#ifndef UWORD
typedef uint16_t  UWORD;
#endif

// common RGB style triplet,
// order of color components always "RGB",
// may be preceded by a zeroed byte for 32-bit storage on TurboSilver objects..
//
typedef UBYTE COLOR[3];

// decimal numbers are stored in 32-bit integers
// which must be divided by 65536 for actual floating-point value..
typedef int32_t FRACT;

// from spec, XYZ pos in triplets
typedef struct vector
{
	FRACT X;
	FRACT Y;
	FRACT Z;
} VECTOR;

// from spec, pos points as matrix
typedef struct matrix
{
	VECTOR I;
	VECTOR J;
	VECTOR K;
} MATRIX;

// from spec, transformation matrix structure
typedef struct tform
{
	VECTOR r;
	VECTOR a;
	VECTOR b;
	VECTOR c;
	VECTOR s;
} TFORM;

// from spec, cell for generating animated cells,
// can be attached to object or camera
typedef struct story
{
	UBYTE Path[18]; /* name of object in cell data */
	VECTOR Translate;
	VECTOR Rotate;
	VECTOR Scale;
	UWORD info;
} STORY;


// object node for handling/containing object data:
// this is from scratch according to description of how nodes are related..
//
class IobNode;
class IobNode
{
public:
	IobNode()
		: left(NULL)
		, right(NULL)
		, up(NULL)
		, down(NULL)
	{}
	~IobNode()
	{}

	// siblings in tree-like hierarchy
	// (top level, left-to-right)
	//
	// CHECK: are siblings used only on "top-level" of hiearchy?
	IobNode *left;
	IobNode *right;

	// descendants in dbl-linked
	// hierarchy chain (top-to-down)
	IobNode *up;
	IobNode *down;

	// TODO: also node data needs to be stored here..
};

class CIobReader
{
private:
	// size of file according to file header:
	// actual size - 8 bytes (IFF FORM tag and size field)
	uint32_t m_size;

	// amount read so far..
	uint32_t m_read;

	// head-node of object node hierarchy
	// (need somewhere to start..),
	// we don't know amount of nodes until all are found..?
	//
	IobNode *m_head;

	// TODO: check better way:
	// we need to distinguish when next node
	// is child or sibling of a previous node..
	//
	IobNode *m_currentChild;
	IobNode *m_currentSibling;

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

	// helper and to detect uses of converted values:
	// 32-bit integer to floating point..
	//
	float FractToFloat(const FRACT frval)
	{
		return (frval/65536.0);
	}

	// handle data in chunk (if supported)
	bool handleChunk(CIOBuffer &buffer, unsigned int chunkID, unsigned int chunkSize);

	// read&handle each chunk in file (if supported)
	bool readChunks(CAnsiFile &file, CIOBuffer &buffer);

public:
    CIobReader();

	bool readFile(CAnsiFile &file);
};

#endif // IOBREADER_H
