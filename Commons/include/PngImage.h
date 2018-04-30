#ifndef SH_PNGIMAGE_H 
#define SH_PNGIMAGE_H

#include "Commons.h"
#include "ShString.h"
#include "ShFile.h"

namespace Shady
{
	enum ChunkType : s32
	{
		IHDR = 0x52444849,
		PLTE = 0x45544C50,
		IDAT = 0x54414449,
		IEND = 0x444E4549,
		bKGD = 0x44474B62,
		cHRM = 0x4D524863,
		dSIG = 0x47495364,
		eXIf = 0x66495865,
		gAMA = 0x414D4167,
		hIST = 0x54534968,
		iCCP = 0x50434369,
		iTXt = 0x74585469,
		pHYs = 0x73594870,
		sBIT = 0x54494273,
		sPLT = 0x544C5073,
		sRGB = 0x42475273,
		sTER = 0x52455473,
		tEXt = 0x74584574,
		tIME = 0x454D4974,
		tRNS = 0x534E5274,
		zTXt = 0x7458547A
	};

	enum PngColorType
	{
		GREYSCALE = 0,
		TRUECOLOR = 2,
		INDEXED = 3,
		GREYSCALE_A = 4,
		TRUECOLOR_A = 6
	};

	struct PngChunk
	{
		s32 Length;
		s32 Type;
		c8* Data;
		s32 ChunkChecksum;
		b8 IsValid;
		s32 TotalSize;
	};

	
	b8 IsValidChunk(c8* Data);
	b8 IsChunkCritical(s32 Type);
	PngChunk GetNextChunk(c8* Data);
	

	struct PngImage
	{
		b8 IsValid;

		s32 Width;
		s32 Height;
		s8 BitDepth; // Per channel, not pixel
		s8 ColorType;
		s8 CompressionMethod;
		s8 FilterMethod;
		s8 InterlaceMethod;
		b8 IsSRGB;

		c8* Data;

		b8 InitFromFile(const String& FileName);
		b8 InitFromData(BinaryFileContent FileContent);

	};
}

#endif
