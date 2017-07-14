#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <Commons.h>
#include <fstream>
#include <cstdio>
#include <Windows.h>
#include "ShString.h"

namespace Shady
{
	struct BinaryFileContent
	{
		void* contents;
		u32 sizeInBytes;
	};
	namespace File
	{
		uint64 getSize(const char* fileName);
		char* readTextFile(const char* fileName);
		void readObj2(const char* fileName);
		String win32ReadTextFile(const char* fileName);
		String win32ReadTextFile(const String& fileName);
		BinaryFileContent win32ReadBinaryFile(const char* fileName);
		BinaryFileContent win32ReadBinaryFile(const String& fileName);
		BinaryFileContent readBinaryFile(const char* fileName);
		b8 win32WriteFile(const char* fileName, void* memory, u32 memSize);
	}
	
}

#endif
