#include "ShString.h"



namespace Shady
{
	void String::InitBuffer(u32 size)
	{
		mBufferSize = size;
		mBuffer = new c8[mBufferSize];
	}

	String::String():mBufferSize(0), mBuffer(0)
	{
		
	}

	String::String(std::initializer_list<const char*> list):
		mBufferSize{0}, mBuffer{0}
	{
		u32 numOfStrings = list.size();
		
		for(auto it = list.begin(); it != list.end(); it++)
		{
			mBufferSize += StrLength(*it);
		}
		
		mBufferSize++; //for null terminator
		mBuffer = new c8[mBufferSize];
		c8* tempBuffer = mBuffer;
		for(auto it = list.begin(); it != list.end(); it++)
		{
			s32 advanceBy = StrCopyNoTerminator(tempBuffer, *it);
			tempBuffer += advanceBy;
		}
		*tempBuffer = '\0';
		
	}

	String::String(u32 integer)
	{
		u32 size = DigitCount(integer, 10);
		mBufferSize = size + 1;
		mBuffer = new c8[mBufferSize];
		S32ToStr(mBuffer, mBufferSize, integer);
	}
	String::String(const c8* str)
	{
		mBufferSize = StrLength(str) + 1;
		mBuffer = new c8[mBufferSize];
		StrCopy(mBuffer, str);
	}
	String::String(const String& other): mBufferSize(other.mBufferSize), mBuffer(0)
	{
		if(mBufferSize > 0)
		{
			mBuffer = new c8[mBufferSize];
			StrCopy(mBuffer, other.mBuffer);
		}
	}
	String::String(String&& other)
	{
		this->mBuffer = other.mBuffer;
		other.mBuffer = 0;
		this->mBufferSize = other.mBufferSize;
	}

	String::String(s32 numOfStrings, ...)
	{
		va_list argList;
		va_start(argList, numOfStrings);
		mBufferSize = 0;

		s32 stringsFound = 0;
		//TODO optimize
		c8** strings = new c8*[numOfStrings];
		while(numOfStrings--)
		{
			c8* str = (c8*)va_arg(argList, c8*);
			if(str)
			{
				strings[stringsFound++] = str;
				mBufferSize += StrLength(str);
			}
		}
		
		mBuffer = new c8[mBufferSize];
		c8* tempBuffer = mBuffer;
		for(u32 strIndex = 0; strIndex < stringsFound; strIndex++)
		{
			s32 advanceBy = StrCopyNoTerminator(tempBuffer, strings[strIndex]);
			tempBuffer += advanceBy;
		}
		*tempBuffer = '\0';
		delete[] strings;
		va_end(argList);
	}

	String& String::operator=(const String& other)
	{
		mBufferSize = other.mBufferSize;
		if(!mBuffer) mBuffer = new c8[mBufferSize];
		StrCopy(mBuffer, other.mBuffer);
		return *this;
	}
	String& String::operator=(const c8* str)
	{
		SH_ASSERT(str);
		s32 size = StrLength(str);
		
		mBufferSize = size + 1;
		mBuffer = new c8[mBufferSize];	
		strcpy(mBuffer, str);
		
		return *this;
	}
	const c8* String::CStr() const
	{
		return mBuffer;
	}
	void String::Reserve(u32 size)
	{
		if(!mBuffer)
		{
			InitBuffer(size + 1);
		}
		else if(size > mBufferSize)
		{
			c8* tempBuffer = new c8[size + 1];
			StrCopy(tempBuffer, mBuffer);
			delete[] mBuffer;
			mBuffer = tempBuffer;
		}
		else
		{
			c8* tempBuffer = new c8[size + 1];
			StrnCopy(tempBuffer, size, tempBuffer);
			delete[] mBuffer;
			mBuffer = tempBuffer;
		}
	}

	u32 String::Size() const 
	{
		return mBufferSize - 1;
	}

	c8& String::operator[](s32 index)
	{
		SH_ASSERT((index > 0) && (index < mBufferSize));
		return *(mBuffer + index);
	}

	b8 String::operator==(const String& other) const
	{
		return StrCompare(mBuffer, other.mBuffer);
	}
	b8 String::operator!=(const String& other) const 
	{
		return !((*this) == other);
	}

	String String::operator+(const c8* str)
	{
		u32 len = StrLength(str);
		if(len > 0)
		{
			String result;
			result.InitBuffer(mBufferSize + len);

			c8* tempBuffer = result.mBuffer;
			c8* tempMBuffer = mBuffer;
			while(*tempMBuffer) *tempBuffer++ = *tempMBuffer++;
			while(*str) *tempBuffer++ = *str++;
			(*tempBuffer)	= '\0';
			return result;
		}
		
		return *this;
	}

	String String::operator+(const c8 c)
	{
		String result;
		if(mBuffer)
		{
			result.InitBuffer(mBufferSize + 1);
			StrCopyNoTerminator(result.mBuffer, mBuffer);
			*(result.mBuffer + result.mBufferSize - 2) = c;
			*(result.mBuffer + result.mBufferSize - 1) = '\0';
		}
		else
		{
			result.InitBuffer(2);
			result.mBuffer[0] = c;
			result.mBuffer[1] = '\0';
		}
		return result;
	}

	String String::operator+(s32 num)
	{
		String result;
		c8* temp = S32ToStr(num);

		result.InitBuffer(mBufferSize + StrLength(temp));
		StrCopyNoTerminator(result.mBuffer, mBuffer);
		StrCopy(result.mBuffer + mBufferSize-1, temp);

		delete[] temp;
		return result;
	}

	String String::operator+(const String& other)
	{
		const c8* str = other.CStr();
		u32 len = other.Size();
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
		if(str)
		{
			u32 len = StrLength(str);
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
		}
		return *this;
	}

	String& String::operator+=(const c8 c)
	{
		if(mBuffer)
		{
			c8* oldBuf = mBuffer;
			InitBuffer(mBufferSize + 1);
			StrCopyNoTerminator(mBuffer, oldBuf);
			mBuffer[mBufferSize - 2] = c;
			mBuffer[mBufferSize - 1] = '\0';
			delete[] oldBuf;
		}
		else
		{
			InitBuffer(2);
			mBuffer[0] = c;
			mBuffer[1] = '\0';
		}
		return *this;
	}
	String& String::operator+=(const String& other)
	{
		const c8* str = other.CStr();
		u32 len = other.Size();
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

	String::operator b8()
	{
		b8 result = false;
		if(mBuffer)
		{
			if(mBufferSize > 0)
			{
				if(mBuffer[0] != '\0')
				{
					result = true;
				}  
			}
			else
			{
				result = false;
			}
			
		}
		return result;
	}

	b8 String::CmpIgnoreCase(const String& other)
	{
		return StrCompareNoCase(mBuffer, other.mBuffer);
	}

	String String::SubString(u32 beginIndex, u32 numOfElem)
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

	Array<String> String::Split(c8 token)
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
				result.Add(temp);
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
			result.Add(temp);
		}
		return result;
	}

	f32 String::Tof32()
	{
		//TODO replace with own implementation
		f32 result = 0;
		sscanf(mBuffer, "%f", &result);
		return result;
	}

	f64 String::Tof64()
	{
		f64 result = 0;
		sscanf(mBuffer, "%lf", &result);
		return result;
	}

	s32 String::Tos32()
	{
		return StrTos32(mBuffer);
	}

	String String::GetLine()
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
				chars.Add('\0');
				lineBeginIndex = ++charIndex;
				break;
			}
			chars.Add(currentChar);
		}
		return String(&chars[0]);
	}

	b8 String::BeginsWith(c8 character)
	{
		return (mBuffer[0] == character);
	}

	b8 String::BeginsWith(const char* str)
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