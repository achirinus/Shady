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
		if(!mBuffer) mBuffer = new c8[mBufferSize];
		strCopy(mBuffer, other.mBuffer);
		return *this;
	}
	String& String::operator=(const c8* str)
	{
		SH_ASSERT(str);
		s32 size = strLength(str);
		
		mBufferSize = size + 1;
		mBuffer = new c8[mBufferSize];	
		strcpy(mBuffer, str);
		
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

	u32 String::size() const 
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
	b8 String::operator!=(const String& other)
	{
		return !((*this) == other);
	}

	String String::operator+(const c8* str)
	{
		u32 len = strLength(str);
		if(len > 0)
		{
			String result;
			result.mBufferSize = mBufferSize + len;
			result.mBuffer = new c8[result.mBufferSize];
			c8* tempBuffer = result.mBuffer;
			c8* tempMBuffer = mBuffer;
			while(*tempMBuffer) *tempBuffer++ = *tempMBuffer++;
			while(*str) *tempBuffer++ = *str++;
			(*tempBuffer)	= '\0';
			return result;
		}
		
		return *this;
	}

	String String::operator+(const String& other)
	{
		const c8* str = other.cStr();
		u32 len = other.size();
		if(len > 0)
		{
			String result;
			result.mBufferSize = mBufferSize + len;
			result.mBuffer = new c8[result.mBufferSize];
			c8* tempBuffer = result.mBuffer;
			c8* tempMBuffer = mBuffer;
			while(*tempMBuffer) *tempBuffer++ = *tempMBuffer++;
			while(*str) *tempBuffer++ = *str++;
			(*tempBuffer)	= '\0';
			return result;
		}
		
		return *this;

	}
	String& String::operator+=(const c8* str)
	{
		u32 len = strLength(str);
		if(len > 0)
		{
			mBufferSize = mBufferSize + len;
			c8* temp = new c8[mBufferSize];
			c8* tempBuffer = temp;
			c8* tempMBuffer = mBuffer;
			while(*tempMBuffer) *tempBuffer++ = *tempMBuffer++;
			while(*str) *tempBuffer++ = *str++;
			(*tempBuffer)	= '\0';
			delete[] mBuffer;
			mBuffer = temp;
		}
		return *this;
	}
	String& String::operator+=(const String& other)
	{
		const c8* str = other.cStr();
		u32 len = other.size();
		if(len > 0)
		{
			mBufferSize = mBufferSize + len;
			c8* temp = new c8[mBufferSize];
			c8* tempBuffer = temp;
			c8* tempMBuffer = mBuffer;
			while(*tempMBuffer) *tempBuffer++ = *tempMBuffer++;
			while(*str) *tempBuffer++ = *str++;
			(*tempBuffer)	= '\0';
			delete[] mBuffer;
			mBuffer = temp;
		}
		return *this;
	}

	b8 String::cmpIgnoreCase(const String& other)
	{
		return strCompareNoCase(mBuffer, other.mBuffer);
	}

	String String::subString(u32 beginIndex, u32 numOfElem)
	{
		SH_ASSERT(beginIndex >= 0);
		SH_ASSERT(beginIndex < mBufferSize);
		SH_ASSERT((beginIndex + numOfElem) < mBufferSize);
		String result = {};
		result.mBufferSize = numOfElem + 1;
		result.mBuffer = new c8[result.mBufferSize];
		for(u32 charIndex = beginIndex; charIndex <= numOfElem; charIndex++)
		{
			result.mBuffer[charIndex] = this->mBuffer[charIndex];
		}
		result.mBuffer[mBufferSize - 1] = '\0';
		return result;
	}

	Array<String> String::split(c8 token)
	{
		Array<String> result {};
		u32 lastIndex = 0;
		for(u32 charIndex = 0; charIndex < mBufferSize; charIndex++)
		{
			if(mBuffer[charIndex] == token)
			{
				u32 charsFound = charIndex - lastIndex;
				String temp{charsFound};
				for(u32 tempIndex = 0; tempIndex < charsFound; tempIndex++)
				{
					temp.mBuffer[tempIndex] = this->mBuffer[lastIndex++];
				}
				lastIndex++;
				temp.mBuffer[temp.mBufferSize - 1] = '\0';
				result.add(temp);
			}
		}
		if(lastIndex < mBufferSize)
		{
			u32 charRemaining = (mBufferSize - 1) - lastIndex;
			String temp {charRemaining};
			for(u32 charIndex = 0; charIndex < charRemaining; charIndex++)
			{
				temp.mBuffer[charIndex] = this->mBuffer[lastIndex++];
			}
			temp.mBuffer[temp.mBufferSize - 1] = '\0';
			result.add(temp);
		}
		return result;
	}

	f32 String::toFloat()
	{
		//TODO replace with own implementation
		f32 result = 0;
		sscanf(mBuffer, "%f", &result);
		return result;
	}

	f64 String::toDouble()
	{
		f64 result = 0;
		sscanf(mBuffer, "%lf", &result);
		return result;
	}

	s32 String::toInt()
	{
		s32 result = 0;
		sscanf(mBuffer, "%d", &result);
		return result;
	}

	String String::getLine()
	{
		
		//TODO optimize this!
		static u32 lineBeginIndex = 0;
		if(lineBeginIndex == U32_MAX)
		{
			return String(SH_STRING_ENDED);
		}
		Array<c8> chars{};
		for(u32 charIndex = lineBeginIndex; charIndex < mBufferSize; charIndex++)
		{
			c8 currentChar = mBuffer[charIndex];
			if(currentChar == '\0')
			{
				lineBeginIndex = U32_MAX;
			}
			if(currentChar == '\r') continue;
			if(currentChar == '\n')
			{
				chars.add('\0');
				lineBeginIndex = ++charIndex;
				break;
			}
			chars.add(currentChar);
		}
		return String(&chars[0]);
	}

	b8 String::beginsWith(c8 character)
	{
		return (mBuffer[0] == character);
	}

	b8 String::beginsWith(const char* str)
	{
		b8 result = true;
		if(mBuffer)
		{
			c8* temp = mBuffer;
			while(*str)
			{
				if(*str++ != *temp++) result = false;
			}
		}
		return result;
	}

	String::~String()
	{
		if(mBuffer)
		{
			delete[] mBuffer;
		}
	}
}