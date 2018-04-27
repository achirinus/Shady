#include "FileUtils.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <Windows.h>

#pragma warning(disable:4996)

namespace Shady
{
	
		namespace File
		{

			void SetCwd(const c8* path)
			{
				SetCurrentDirectoryA(path);
			}

			u64 GetSize(const c8* fileName)
			{
				uint64 size = 0;
				HANDLE fileHandle = CreateFileA(fileName,
					GENERIC_READ,
					FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL);
				SH_ASSERT(fileHandle != INVALID_HANDLE_VALUE);
				size = GetFileSize(fileHandle, NULL);
				return size;
			}

			String ReadTextFile(const c8* fileName)
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
				String result(str);
				delete[] str;
				CloseHandle(fileHandle);
				return result;
			}

			String ReadTextFile(const String& fileName)
			{
				return ReadTextFile(fileName.CStr());	
			}

			void ClearContent(BinaryFileContent* fileContent) 
			{
				if (fileContent)
				{
					VirtualFree(fileContent->Data, fileContent->Size, MEM_RELEASE);
					fileContent->Data = 0;
				}
			}

			BinaryFileContent ReadBinaryFile(const char* fileName)
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

			BinaryFileContent ReadBinaryFile(const String& fileName)
			{
				return ReadBinaryFile(fileName.CStr());
			}

			b8 CreateAndWriteFile(const char* fileName, void* memory, u32 memSize)
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