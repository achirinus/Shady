#include "ShString.h"

namespace Shady
{
	String::String():mBufferSize(0), mBuffer(0)
	{

	}
	String::String(const c8* str)
	{
		mBufferSize = strLength(str) + 1;
		mBuffer = new c8[mBufferSize];
		strCopy(mBuffer, str);
	}
	String::String(u32 size)
	{
		mBufferSize = size + 1;
		mBuffer = new c8[mBufferSize];
	}
	String::String(const String& other)
	{
		
		mBufferSize = other.mBufferSize;
		if(mBufferSize > 0)
		{
			mBuffer = new c8[mBufferSize];
			strCopy(mBuffer, other.mBuffer);
		}
	}
	String::String(String&& other)
	{
		this->mBuffer = other.mBuffer;
		other.mBuffer = 0;
		this->mBufferSize = other.mBufferSize;
	}
	String& String::operator=(const String& other)
	{
		mBufferSize = other.mBufferSize;
		strCopy(mBuffer, other.mBuffer);
		return *this;
	}
	String& String::operator=(const c8* str)
	{
		SH_ASSERT(str);
		s32 size = strLength(str);
		if(size < mBufferSize)
		{
			strcpy(mBuffer, str);
			mBufferSize = size +1;
		}
		return *this;
	}
	const c8* String::cStr() const
	{
		return mBuffer;
	}
	void String::reserve(u32 size)
	{
		if(!mBuffer)
		{
			mBufferSize = size + 1;
			mBuffer = new c8[mBufferSize];
		}
		else if(size > mBufferSize)
		{
			c8* tempBuffer = new c8[size + 1];
			strCopy(tempBuffer, mBuffer);
			delete[] mBuffer;
			mBuffer = tempBuffer;
		}
		else
		{
			c8* tempBuffer = new c8[size + 1];
			strnCopy(tempBuffer, size, tempBuffer);
			delete[] mBuffer;
			mBuffer = tempBuffer;
		}
	}

	inline u32 String::size() const 
	{
		return mBufferSize - 1;
	}

	c8& String::operator[](s32 index)
	{
		SH_ASSERT((index > 0) && (index < mBufferSize));
		return *(mBuffer + index);
	}

	b8 String::operator==(const String& other)
	{
		return strCompare(mBuffer, other.mBuffer);
	}

	b8 String::cmpIgnoreCase(const String& other)
	{
		return strCompareNoCase(mBuffer, other.mBuffer);
	}

	String String::subString(u32 beginIndex, u32 endIndex)
	{
		SH_ASSERT(beginIndex >= 0);
		SH_ASSERT(beginIndex < mBufferSize);
	}

	String::~String()
	{
		if(mBuffer)
		{
			delete[] mBuffer;
		}
	}
}