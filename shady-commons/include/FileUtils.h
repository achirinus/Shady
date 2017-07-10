#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <Commons.h>
#include <fstream>
#include <cstdio>
#include <Windows.h>
#include "ShString.h"

namespace Shady
{
	
	namespace File
	{
		uint64 getSize(const char* fileName);
		char* readTextFile(const char* fileName);
		void readObj2(const char* fileName);
		String win32ReadTextFile(const char* fileName);
	}
	
}

#endif
