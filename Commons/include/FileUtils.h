#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <Commons.h>
#include "ShString.h"

namespace Shady
{
	struct BinaryFileContent
	{
		void* Data;
		u32 Size;
	};
	namespace File
	{
		void ClearContent(BinaryFileContent* fileContent);
		void SetCwd(const c8* path);
		u64 GetSize(const c8* fileName);
		
		String ReadTextFile(const c8* fileName);
		String ReadTextFile(const String& fileName);
		BinaryFileContent ReadBinaryFile(const char* fileName);
		BinaryFileContent ReadBinaryFile(const String& fileName);
		b8 CreateAndWriteFile(const char* fileName, void* memory, u32 memSize);
	}
	
}

#endif
