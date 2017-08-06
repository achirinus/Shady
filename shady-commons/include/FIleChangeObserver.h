#ifndef SH_FILE_CHANGE_OBSERVER_H
#define SH_FILE_CHANGE_OBSERVER_H

#include "ShadyAssert.h"
#include "ShadyTypes.h"
#include "ShMap.h"
#include "ShArray.h"
#include "ShString.h"
#include "Windows.h"

//This thing saves opens the files to be tracked and keep HANDLES saved.
//Should I only open files on update in case I have too many HANDLES?

namespace Shady
{
	typedef void (*FileChangeCallback)();
	struct FileObserverInfo
	{
		HANDLE fileHandle;
		FileChangeCallback callback;
		SYSTEMTIME lastModified;
		c8 fileName[256];
	};

	class FileChangeObserver
	{
	private:
		Array<FileObserverInfo> obsInfos;

		SYSTEMTIME getLastModified(HANDLE file);
	public:
		FileChangeObserver() = default;
		~FileChangeObserver();
		b8 add(const c8* fileName, FileChangeCallback cb);
		b8 remove(const c8* fileName);
		void update();
	};
}

#endif