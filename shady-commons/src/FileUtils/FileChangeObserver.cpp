#include "FileChangeObserver.h"

namespace Shady
{
	SYSTEMTIME FileChangeObserver::getLastModified(HANDLE file)
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

	b8 FileChangeObserver::add(const c8* fileName, FileChangeCallback cb)
	{
		b8 result = true;
		HANDLE tempHandle = CreateFileA(fileName, GENERIC_READ,
										FILE_SHARE_READ | FILE_SHARE_WRITE,
										NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);
		if(tempHandle != INVALID_HANDLE_VALUE)
		{
			FileObserverInfo tempInfo = {};
			tempInfo.fileHandle = tempHandle;
			tempInfo.callback = cb;
			tempInfo.lastModified = getLastModified(tempHandle);
			strCopy(tempInfo.fileName, fileName);
			obsInfos.add(tempInfo);
		}
		else
		{
			result = false;
		}
		return result;
	}

	b8 FileChangeObserver::remove(const c8* fileName)
	{
		b8 result = false;
		
		for(u32 index = 0; index < obsInfos.size(); index++)
		{
			if(strCompare(fileName, obsInfos[index].fileName))
			{
				result = true;
				CloseHandle(obsInfos[index].fileHandle);
				obsInfos.remove(index);
			}
		}
		return result;
	}

	void FileChangeObserver::update()
	{
		for(u32 i = 0; i < obsInfos.size(); i++)
		{
			SYSTEMTIME lastModified = getLastModified(obsInfos[i].fileHandle);
			if((lastModified.wYear == obsInfos[i].lastModified.wYear) && 
				(lastModified.wMonth == obsInfos[i].lastModified.wMonth) &&
				(lastModified.wDay == obsInfos[i].lastModified.wDay) &&
				(lastModified.wHour == obsInfos[i].lastModified.wHour) &&
				(lastModified.wMinute == obsInfos[i].lastModified.wMinute) &&
				(lastModified.wSecond == obsInfos[i].lastModified.wSecond) &&
				(lastModified.wMilliseconds == obsInfos[i].lastModified.wMilliseconds))
			{
				//Not edited	
			}
			else
			{
				obsInfos[i].lastModified = lastModified;
				if(obsInfos[i].callback) obsInfos[i].callback();
			}

		}
	}
}