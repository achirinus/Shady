#include "FileChangeObserver.h"

namespace Shady
{

	FileChangeObserver* FileChangeObserver::sInstance = nullptr;

	FileChangeObserver* FileChangeObserver::GetInstance()
	{
		if(!sInstance) sInstance = new FileChangeObserver();

		return sInstance;
	}

	SYSTEMTIME FileChangeObserver::GetLastModified(HANDLE file)
	{
		SYSTEMTIME result = {};
		BY_HANDLE_FILE_INFORMATION info = {};
		GetFileInformationByHandle(file, &info);
		FileTimeToSystemTime(&info.ftLastWriteTime, &result);
		return result;
	}

	FileChangeObserver::~FileChangeObserver()
	{
		for(u32 index = 0 ; index < obsInfos.size(); index++)
		{
			CloseHandle(obsInfos[index].fileHandle);
		}
	}

	b8 FileChangeObserver::Add(const c8* fileName, FileChangeCb cb)
	{
		b8 result = true;
		HANDLE tempHandle = CreateFileA(fileName, GENERIC_READ,
										FILE_SHARE_READ | FILE_SHARE_WRITE,
										NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
		if(tempHandle != INVALID_HANDLE_VALUE)
		{
			FileObserverInfo tempInfo = {};
			tempInfo.fileHandle = tempHandle;
			tempInfo.cb = cb;
			tempInfo.lastModified = GetLastModified(tempHandle);
			StrCopy(tempInfo.fileName, fileName);
			obsInfos.add(tempInfo);
		}
		else
		{
			result = false;
		}
		return result;
	}

	b8 FileChangeObserver::Add(const c8* fileName, Object* obj, FileChangeObjCb objCb)
	{
		b8 result = true;
		HANDLE tempHandle = CreateFileA(fileName, GENERIC_READ,
										FILE_SHARE_READ | FILE_SHARE_WRITE,
										NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
		if(tempHandle != INVALID_HANDLE_VALUE)
		{
			FileObserverInfo tempInfo = {};
			tempInfo.fileHandle = tempHandle;
			tempInfo.obj = obj;
			tempInfo.objCb = objCb;
			tempInfo.lastModified = GetLastModified(tempHandle);
			StrCopy(tempInfo.fileName, fileName);
			obsInfos.add(tempInfo);
		}
		else
		{
			result = false;
		}
		return result;
	}

	b8 FileChangeObserver::Remove(const c8* fileName)
	{
		b8 result = false;
		
		for(u32 index = 0; index < obsInfos.size(); index++)
		{
			if(StrCompare(fileName, obsInfos[index].fileName))
			{
				result = true;
				CloseHandle(obsInfos[index].fileHandle);
				obsInfos.remove(index);
			}
		}
		return result;
	}

	void FileChangeObserver::Update()
	{
		for(u32 i = 0; i < obsInfos.size(); i++)
		{
			FileObserverInfo& info = obsInfos[i];
			SYSTEMTIME lastModified = GetLastModified(info.fileHandle);
			if((lastModified.wYear == info.lastModified.wYear) && 
				(lastModified.wMonth == info.lastModified.wMonth) &&
				(lastModified.wDay == info.lastModified.wDay) &&
				(lastModified.wHour == info.lastModified.wHour) &&
				(lastModified.wMinute == info.lastModified.wMinute) &&
				(lastModified.wSecond == info.lastModified.wSecond) &&
				(lastModified.wMilliseconds == info.lastModified.wMilliseconds))
			{
				//Not edited	
			}
			else
			{
				info.lastModified = lastModified;
				if(info.cb) info.cb();
				if(info.objCb && info.obj) (info.obj->*info.objCb)();
			}

		}
	}
}