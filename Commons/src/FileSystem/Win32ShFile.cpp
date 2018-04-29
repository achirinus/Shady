#include "ShFile.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>
#include <Windows.h>
#include "Win32Utils.h"
#include "ComFuncs.h"

#pragma warning(disable:4996)

namespace Shady
{
	File::File() :WriteCursor{ 0 }, ReadCursor{ 0 }, Handle{ 0 }, Type{ FileType::BINARY_FILE }, IsOpen{ 0 }, Path{}
	{

	}

	File::File(const String& fileName) : WriteCursor{ 0 }, ReadCursor{ 0 }, Handle{ 0 }, Type{ FileType::BINARY_FILE }, IsOpen{ 0 }, Path{fileName}
	{

	}

	File::~File()
	{
		Close();
	}
	b8 File::Open(FileType type, FileOption option)
	{
		if (Path.IsEmpty()) return false;
		b8 Result = true;
		DWORD DesiredAccess = GENERIC_READ | GENERIC_WRITE;
		DWORD ShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ;
		DWORD CreationDisposition = 0;
		switch (option)
		{
		case FileOption::OPEN_ALWAYS_NEW:
			CreationDisposition = CREATE_ALWAYS;
			break;
		case FileOption::OPEN_ONLY_NEW:
			CreationDisposition = CREATE_NEW;
			break;
		case FileOption::OPEN_NORMAL:
			CreationDisposition = OPEN_ALWAYS;
			break;
		case FileOption::OPEN_ONLY_EXISTING:
			CreationDisposition = OPEN_EXISTING;
			break;
		case FileOption::OPEN_REPLACE:
			CreationDisposition = TRUNCATE_EXISTING;
			break;
		}
		DWORD FlagsAndAttribs = FILE_ATTRIBUTE_NORMAL;
		this->Handle = CreateFileA(Path.CStr(), DesiredAccess, ShareMode, 0, CreationDisposition, FlagsAndAttribs, 0);
		if (this->Handle == INVALID_HANDLE_VALUE)
		{
			Result = false;
			Win32::CheckLastError();
			//TODO Set Read/Write Cursors based on open type
		}
		this->IsOpen = true;
		return Result;
	}
	b8 File::Open(const String& fileName, FileType type, FileOption option)
	{
		this->Path = fileName;
		return Open(type, option);
	}

	void File::Close()
	{
		if (Handle && IsOpen)
		{
			CloseHandle(Handle);
			IsOpen = false;
			WriteCursor = 0;
			ReadCursor = 0;
			Handle = 0;
		}
	}

	u64 File::GetSize()
	{
		u64 Result = 0;
		if (!Handle || !IsOpen) return Result;
		u32 HighValue = 0;
		u32 LowValue = GetFileSize(Handle, (LPDWORD)&HighValue);
		Result |= HighValue;
		Result <<= 32;
		Result |= LowValue;

		return Result;
	}

	void File::SetWriteCursor(FileCursorPos cursorPos)
	{
		if (!Handle || !IsOpen) return;
		switch (cursorPos)
		{
		case FileCursorPos::BEGIN:
		{
			WriteCursor = 0;
		}break;
		case FileCursorPos::END:
		{
			u64 FileSize = GetSize();
			WriteCursor = FileSize;
		}break;
		}
	}

	void File::SetWriteCursor(u64 cursorPos)
	{
		WriteCursor = cursorPos;
	}
	void File::AdvanceWriteCursor(u32 offset)
	{
		WriteCursor += offset;
	}
		
	String File::ReadAllText()
	{
		if (!Handle || !IsOpen) return String{};
		u64 FileSize = GetSize();
		c8* TempBuffer = new c8[FileSize];
		SetFilePointer(Handle, 0, 0, FILE_BEGIN);
		ReadFile(Handle, (void*)TempBuffer, FileSize, NULL, NULL);
		TempBuffer[FileSize] = 0;
		SetFilePointer(Handle, 0, 0, FILE_BEGIN);
		return String::FromAlocatedCStr(TempBuffer);
	}

	String File::ReadLine()
	{
		if (!Handle || !IsOpen) return String{};
		LARGE_INTEGER LargeReadCursor;
		LARGE_INTEGER NewReadCursor;
		LargeReadCursor.QuadPart = ReadCursor;
		SetFilePointerEx(Handle, LargeReadCursor, &NewReadCursor, FILE_BEGIN);
		u64 FileSize = GetSize();
		u64 BufferSize = FileSize - NewReadCursor.QuadPart;
		c8* TempBuffer = new c8[BufferSize + 1];
		if (!ReadFile(Handle, TempBuffer, BufferSize, NULL, NULL))
		{
			Win32::CheckLastError();
			return String{};
		}
		TempBuffer[BufferSize] = 0;
		c8* NewLine = FindStr(TempBuffer, "\r\n");
		b8 LastLine = false;
		u32 CharsToPass = 0;
		if (!NewLine)
		{
			NewLine = FindStr(TempBuffer, "\n");
			if (!NewLine)
			{
				if (BufferSize)
				{
					LastLine = true;
				}
				else
				{
					return String{};
				}
			}
			else
			{
				CharsToPass = 1;
			}
		}
		else
		{
			CharsToPass = 2;
		}
		String Result;

		if (LastLine)
		{
			Result = TempBuffer;
		}
		else
		{
			Result = String::FromLimitedStr( TempBuffer, (u32)(NewLine - TempBuffer));
		}
		delete[] TempBuffer;
		
		if (!Result.Size()) return String{};
		LargeReadCursor.QuadPart += Result.Size() + CharsToPass;
		SetFilePointerEx(Handle, LargeReadCursor, &NewReadCursor, FILE_BEGIN);
		ReadCursor = NewReadCursor.QuadPart;
		
		return Move(Result);
	}

	u32 File::ReadData(void* data, u32 size)
	{
		LARGE_INTEGER LargeReadCursor;
		LARGE_INTEGER NewReadCursor;
		LargeReadCursor.QuadPart = ReadCursor;
		SetFilePointerEx(Handle, LargeReadCursor, &NewReadCursor, FILE_BEGIN);
		u32 Result = 0;
		if (!ReadFile(Handle, data, size, (LPDWORD)&Result, NULL))
		{
			Win32::CheckLastError();
			return 0;
		}
		WriteCursor += Result;

		return Result;
	}


	void File::WriteText(const String& text)
	{
		if (!Handle || !IsOpen) return;
		LARGE_INTEGER LargeWriteCursor;
		LARGE_INTEGER NewWriteCursor;
		LargeWriteCursor.QuadPart = WriteCursor;
		SetFilePointerEx(Handle, LargeWriteCursor, &NewWriteCursor, FILE_BEGIN);
		u32 BytesWritten = 0;
		if (!WriteFile(Handle, text.CStr(), text.Size(), (LPDWORD)&BytesWritten, NULL))
		{
			Win32::CheckLastError();
			return;
		}
		WriteCursor += BytesWritten;
	}

	u32 File::WriteData(void* data, u32 size)
	{
		if (!Handle || !IsOpen) return 0;
		LARGE_INTEGER LargeWriteCursor;
		LARGE_INTEGER NewWriteCursor;
		LargeWriteCursor.QuadPart = WriteCursor;
		SetFilePointerEx(Handle, LargeWriteCursor, &NewWriteCursor, FILE_BEGIN);
		u32 Result = 0;
		if (!WriteFile(Handle, data, size, (LPDWORD)&Result, NULL))
		{
			Win32::CheckLastError();
			return 0;
		}
		
		WriteCursor += Result;
		return Result;
	}



	//-------------Statics------------------//
	void File::SetCwd(const c8* path)
	{
		SetCurrentDirectoryA(path);
	}

	u64 File::GetSize(const c8* fileName)
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

	String File::ReadTextFile(const c8* fileName)
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

	String File::ReadTextFile(const String& fileName)
	{
		return ReadTextFile(fileName.CStr());	
	}

	void File::ClearContent(BinaryFileContent* fileContent)
	{
		if (fileContent)
		{
			VirtualFree(fileContent->Data, fileContent->Size, MEM_RELEASE);
			fileContent->Data = 0;
		}
	}

	BinaryFileContent File::ReadBinaryFile(const char* fileName)
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

	BinaryFileContent File::ReadBinaryFile(const String& fileName)
	{
		return File::ReadBinaryFile(fileName.CStr());
	}

	b8 File::CreateAndWriteFile(const char* fileName, void* memory, u32 memSize)
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