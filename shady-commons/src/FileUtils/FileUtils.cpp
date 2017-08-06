#include "FileUtils.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>

#pragma warning(disable:4996)

namespace Shady
{
	
		namespace File
		{

			void setCwd(const char* path)
			{
				SetCurrentDirectoryA(path);
			}

			uint64 getSize(const char* fileName)
			{
				uint64 size = 0;
				FILE* file = fopen(fileName, "r");
				if (file)
				{
					fseek(file, 0, SEEK_END);
					size = ftell(file);
					fclose(file);
				}

				return size;
			}


			char* readTextFile(const char* fileName)
			{
				char* contents = nullptr;
				std::ifstream file(fileName);
				if (file)
				{

					file.seekg(0, file.end);
					u32 size = (u32)file.tellg();
					file.seekg(0, file.beg);

					contents = new char[size + 1];
					file.get(contents, size + 1, NULL);
				}
				return contents;
			}


			float stof(const char* s) {
				float rez = 0, fact = 1;
				if (*s == '-') {
					s++;
					fact = -1;
				};
				for (int point_seen = 0; *s; s++) {
					if (*s == '.') {
						point_seen = 1;
						continue;
					};
					int d = *s - '0';
					if (d >= 0 && d <= 9) {
						if (point_seen) fact /= 10.0f;
						rez = rez * 10.0f + (float)d;
					};
				};
				return rez * fact;
			};

			String win32ReadTextFile(const char* fileName)
			{
				//TODO optimize this shit
				OFSTRUCT ofstr{};
				HANDLE fileHandle = CreateFileA(fileName,
												GENERIC_READ, 
												FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
												NULL,
												OPEN_EXISTING,
												FILE_ATTRIBUTE_NORMAL,
												NULL);
				SH_ASSERT(fileHandle != INVALID_HANDLE_VALUE);
				DWORD fileSize = GetFileSize(fileHandle, NULL);
				DWORD bytesRead = 0;
				c8* str = new c8[fileSize + 1];
				ReadFile(fileHandle, (void*)str, fileSize, &bytesRead, NULL);
				str[fileSize] = '\0';
				return String(str);
			}

			String win32ReadTextFile(const String& fileName)
			{
				return win32ReadTextFile(fileName.cStr());	
			}

			BinaryFileContent win32ReadBinaryFile(const char* fileName)
			{

				void* resultMemory;
				OFSTRUCT ofstr{};
				HANDLE fileHandle = CreateFileA(fileName,
												GENERIC_READ, 
												FILE_SHARE_READ | FILE_SHARE_READ,
												NULL,
												OPEN_EXISTING,
												FILE_ATTRIBUTE_NORMAL,
												NULL);
				SH_ASSERT(fileHandle != INVALID_HANDLE_VALUE);
				LARGE_INTEGER fileSize;
				GetFileSizeEx(fileHandle, &fileSize);
				resultMemory = VirtualAlloc(0, fileSize.QuadPart, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);

				SH_ASSERT(resultMemory);
				SH_ASSERT(fileSize.QuadPart <= 0xFFFFFFFF);
				DWORD bytesRead = 0;
				if(ReadFile(fileHandle, resultMemory, fileSize.QuadPart, &bytesRead, NULL))
				{
					//Figure out why read succeded but we read less bytes than file size
					SH_ASSERT(bytesRead == fileSize.LowPart);
				}
				else
				{
					SH_ASSERT(resultMemory);
					VirtualFree(resultMemory, 0, MEM_RELEASE);
					resultMemory = 0;
				}
				CloseHandle(fileHandle);
				return {resultMemory, bytesRead};
			}

			BinaryFileContent win32ReadBinaryFile(const String& fileName)
			{
				return win32ReadBinaryFile(fileName.cStr());
			}

			BinaryFileContent readBinaryFile(const char* fileName)
			{
				FILE* file;
				BinaryFileContent result{};
				fopen_s(&file, fileName, "rb");
				SH_ASSERT(file != nullptr);
				fseek(file, 0, SEEK_END);
				result.sizeInBytes = ftell(file);
				rewind(file);
				result.contents = new c8[result.sizeInBytes];
				u32 readBytes = fread(result.contents, 1, result.sizeInBytes, file);
				SH_ASSERT(readBytes == result.sizeInBytes);
				return result;
			}

			b8 win32WriteFile(const char* fileName, void* memory, u32 memSize)
			{
				b8 result = false;
				SH_ASSERT(fileName);
				SH_ASSERT(memory && memSize);
				
				HANDLE fileHandle = CreateFileA(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
				
				SH_ASSERT(fileHandle != INVALID_HANDLE_VALUE);

				u32 bytesWritten = 0;

				if(WriteFile(fileHandle, memory, memSize, (DWORD*)&bytesWritten, 0))
				{
					//Write succesfull
					SH_ASSERT(memSize == bytesWritten);
					result = true;
				}
				else
				{
					//TODO log 

				}
				return result;
			}

		}
	
}