#ifndef SH_FILE_H
#define SH_FILE_H

#include <Commons.h>
#include "ShString.h"

namespace Shady
{
	struct BinaryFileContent
	{
		void* Data;
		u32 Size;
	};

#ifdef _WIN32
#include <Windows.h>
	typedef HANDLE PlatformFileHandle;
#endif

	enum class FileOption
	{
		OPEN_NORMAL, // Opens no matter if the file exists or not
		OPEN_ONLY_NEW, //Opens only if file doesn't exist
		OPEN_ALWAYS_NEW, //Opens or replaces a file(if it's writable)
		OPEN_ONLY_EXISTING, // Opens only if it exists
		OPEN_REPLACE // Opens only if it exists and truncates
	};

	enum class FileType
	{
		BINARY_FILE,
		TEXT_FILE
	};

	enum class FileCursorPos
	{
		BEGIN,
		END
	};

	struct File
	{
		u64 ReadCursor;
		u64 WriteCursor;
		PlatformFileHandle Handle;
		FileType Type;
		b8 IsOpen;
		String Path;

		File();
		File(const String& fileName);
		~File();

		b8 Open(FileType type, FileOption option = FileOption::OPEN_NORMAL);
		b8 Open(const String& fileName, FileType type, FileOption option = FileOption::OPEN_NORMAL);
		void Close();
		u64 GetSize();
		void SetWriteCursor(FileCursorPos cursorPos);
		void SetWriteCursor(u64 cursorPos);
		void AdvanceWriteCursor(u32 offset);
		String ReadAllText();
		BinaryFileContent ReadAllData();
		String ReadLine();
		u32 ReadData(void* data, u32 size);

		void WriteText(const String& text);
		u32 WriteData(void* data, u32 size);

		static void SetCwd(const c8* path);
		static void ClearContent(BinaryFileContent* fileContent);
		static u64 GetSize(const c8* fileName);
		static String ReadTextFile(const c8* fileName);
		static String ReadTextFile(const String& fileName);
		static BinaryFileContent ReadBinaryFile(const char* fileName);
		static BinaryFileContent ReadBinaryFile(const String& fileName);
		static b8 CreateAndWriteFile(const char* fileName, void* memory, u32 memSize);
	};
	
}

#endif
