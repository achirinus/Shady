#ifndef SH_FILE_CHANGE_OBSERVER_H
#define SH_FILE_CHANGE_OBSERVER_H

#include "ShAssert.h"
#include "ShTypes.h"
#include "ShArray.h"
#include "ShString.h"
#include "Windows.h"
#include "ShObject.h"

//This thing saves opens the files to be tracked and keep HANDLES saved.
//Should I only open files on update in case I have too many HANDLES?

namespace Shady
{
	using FileChangeCb    = void (*)();
	using FileChangeObjCb = void (Object::*)();
	struct FileObserverInfo
	{
		HANDLE fileHandle;
		Object* obj;
		FileChangeObjCb objCb;
		FileChangeCb cb;
		SYSTEMTIME lastModified;
		c8 fileName[256];
	};

	#define FILE_OBS_FUNC(Func) reinterpret_cast<FileChangeObjCb>(&Func)

	class FileChangeObserver
	{
	private:
		Array<FileObserverInfo> obsInfos;

		static FileChangeObserver* sInstance;

		SYSTEMTIME GetLastModified(HANDLE file);
		FileChangeObserver() = default;
		FileChangeObserver(const FileChangeObserver&) = delete;
		FileChangeObserver& operator=(const FileChangeObserver&) = delete;
	public:
		~FileChangeObserver();

		static FileChangeObserver* GetInstance();

		b8 Add(const c8* fileName, FileChangeCb cb);
		b8 Add(const c8* fileName, Object* obj, FileChangeObjCb objCb);
		b8 Remove(const c8* fileName);
		void Update();
	};
}

#endif