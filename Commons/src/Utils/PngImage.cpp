#include "PngImage.h"
#include "ShFile.h"
#include "MemUtils.h"

namespace Shady
{

	char PngHeader[] = { (c8)0x89, (c8)0x50, (c8)0x4E, (c8)0x47, (c8)0x0D, (c8)0x0A, (c8)0x1A, (c8)0x0A };

	b8 PngImage::InitFromFile(const String& FileName)
	{

		return true;
	}
	b8 PngImage::InitFromData(BinaryFileContent FileContent)
	{
		if (!FileContent.Data || !FileContent.Size) return false;

		u32 SizeOfHeader = sizeof(PngHeader);

		if (!MemoryCompare((c8*)FileContent.Data, PngHeader, SizeOfHeader))
		{
			//.PNG is missing, this does not come from a png file
			return false;
		}
		c8* TempData = (c8*)FileContent.Data;
		TempData += SizeOfHeader;
		PngChunk LastChunk{};
		LastChunk = GetNextChunk(TempData);
		if (LastChunk.Type == ChunkType::IHDR)
		{
			c8* ChunkData = LastChunk.Data;

			Width = SwapEndian(*(s32*)ChunkData);
			ChunkData += 4;
			Height = SwapEndian(*(s32*)ChunkData);
			ChunkData += 4;
			BitDepth = *ChunkData;
			ChunkData++;
			ColorType = *ChunkData;
			ChunkData++;
			CompressionMethod = *ChunkData;
			ChunkData++;
			FilterMethod = *ChunkData;
			ChunkData++;
			InterlaceMethod = *ChunkData;
		}
		TempData += LastChunk.TotalSize;

		Array<PngChunk> DataChunks;
		do
		{
			LastChunk = GetNextChunk(TempData);
			if (LastChunk.Type == ChunkType::IDAT) DataChunks.Add(LastChunk);
			TempData += LastChunk.TotalSize;
		} while (LastChunk.IsValid && LastChunk.Type != ChunkType::IEND);

		return true;
	}

	PngChunk GetNextChunk(c8* Data)
	{
		PngChunk result{};

		if (b8 IsChunkValid = IsValidChunk(Data))
		{
			s32* LengthP = (s32*)Data;
			result.Length = SwapEndian(*LengthP);
			result.Type = *(s32*)(Data + 4);
			result.IsValid = IsChunkValid;
			result.Data = Data + 8;
			result.ChunkChecksum = *(s32*)(result.Data + result.Length);
			result.TotalSize = 12 + result.Length;
		}
		return result;
	}

	b8 IsChunkCritical(s32 Type)
	{
		s32 FirstChar = Type & 0xFF;

		if ((FirstChar >= 65) && (FirstChar <= 90)) return true;
		return false;
	}
	
	//This is not checking everything now, it should also compute and check the checksum
	b8 IsValidChunk(c8* Data)
	{
		s32* ChunkTypeP = (s32*)(Data + 4);
		b8 result = false;
		switch (s32 tt = *ChunkTypeP)
		{
		case ChunkType::IHDR:
		case ChunkType::PLTE:
		case ChunkType::IDAT:
		case ChunkType::IEND:
		case ChunkType::bKGD:
		case ChunkType::cHRM:
		case ChunkType::dSIG:
		case ChunkType::eXIf:
		case ChunkType::gAMA:
		case ChunkType::hIST:
		case ChunkType::iCCP:
		case ChunkType::iTXt:
		case ChunkType::pHYs:
		case ChunkType::sBIT:
		case ChunkType::sPLT:
		case ChunkType::sRGB:
		case ChunkType::sTER:
		case ChunkType::tEXt:
		case ChunkType::tIME:
		case ChunkType::tRNS:
		case ChunkType::zTXt:
			result = true;
			break;
		default: result = false;
		}
		return result;
	}
}