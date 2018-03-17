#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <Commons.h>
#include <fstream>
#include <cstdio>
#include <Windows.h>
#include "ShString.h"

namespace Shady
{
	struct Win32BinaryFileContent
	{
		void* contents;
		u32 sizeInBytes;
		void Clear() { VirtualFree(contents, sizeInBytes, MEM_RELEASE); }
	};
	namespace File
	{
		void setCwd(const char* path);
		uint64 getSize(const char* fileName);
		char* readTextFile(const char* fileName);
		void readObj2(const char* fileName);
		String win32ReadTextFile(const char* fileName);
		String win32ReadTextFile(const String& fileName);
		Win32BinaryFileContent win32ReadBinaryFile(const char* fileName);
		Win32BinaryFileContent win32ReadBinaryFile(const String& fileName);
		Win32BinaryFileContent readBinaryFile(const char* fileName);
		b8 win32WriteFile(const char* fileName, void* memory, u32 memSize);
	}
	
}

#endif
