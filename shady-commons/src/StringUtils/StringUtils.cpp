#include "StringUtils.h"
#include "ShadyMath.h"

namespace Shady
{

	b8 isLetter(c8 c)
	{
		return ((c > 64) && (c < 91)) || ((c > 96) && (c < 123));
	}

	b8 cmpCharsNoCase(c8 c1, c8 c2)
	{
		if (isLetter(c1) && isLetter(c2))
		{
			s32 dif = absolute(c1 - c2);
			if ((dif == 32) || (dif == 0)) return true;

			return false;
		}
		else if (c1 == c2) return true;
		return false;
	}
	
	c8* findChar(c8* str, c8 c)
	{

		if (!str) return nullptr;
		c8* temp = str;
		while (temp != '\0')
		{
			if (*temp == c) return temp;
			temp++;
		}
		return nullptr;
	}

	int getLine(c8* buffer, int bufferLength, c8* str)
	{
		int result = 0;
		for (int i = 0; i < bufferLength; i++)
		{
			if (!*str) break;
			if ((*str == '\r') && (*(str + 1) == '\n'))
			{
				result += 2;
				break;
			}
			if (*str == '\n')
			{
				result++;
				break;
			}
			*buffer++ = *str++;
			result++;
		}
		*buffer = '\0';
		return result;
	}

	c8* findStr(c8* str, c8* strToFind)
	{
		bool found = false;
		c8* value = nullptr;
		c8* tempStr = str;
		while (tempStr != '\0')
		{
			if (*tempStr == *strToFind)
			{
				found = true;
				c8* potetialWinner = tempStr;
				c8* tempStrToFind = strToFind;
				while (*tempStrToFind != '\0')
				{
					if (*tempStr == '\0') return value;
					if (*tempStrToFind != *tempStr) found = false;
					tempStrToFind++;
					tempStr++;
				}
				if (found)
				{
					return potetialWinner;
				}
			}
			tempStr++;
		}
		return value;
	}

	bool strCompare(const c8* str1, const c8* str2)
	{
		
		if (strLength(str1) != strLength(str2)) return false;
		
		while (*str1)
		{
			if (*str1 != *str2) return false;
			str1++;
			str2++;
		}
		return true;
	}

	b8 strCompare(const c16* str1, const c16* str2)
	{
		if (strLength(str1) != strLength(str2)) return false;
		
		while (*str1)
		{
			if (*str1 != *str2) return false;
			str1++;
			str2++;
		}
		return true;
	}

	bool strCompareNoCase(const c8* str1, const c8* str2)
	{
		if (strLength(str1) != strLength(str2)) return false;
		while (*str1 || *str2)
		{
			if (!cmpCharsNoCase(*str1, *str2)) return false;
			str1++;
			str2++;
		}

		return true;
	}

	u32 strLength(const c8 *str)
	{
		u32 result = 0;
		while (*str++) result++;

		return result;
	}
	
	u32 strLength(const c16 *str)
	{
		u32 result = 0;
		while (*str++) result++;

		return result;
	}


	bool endsWith(c8* str, c8* end)
	{
		u32 sizeStr = strLength(str);
		u32 sizeEnd = strLength(end);
		if(sizeEnd > sizeStr) return false;
		bool result = strCompare((str + (sizeStr - sizeEnd)), end);

		return result;
	}

	bool beginsWith(const c8* str, const c8* strToFind)
	{
		b8 result = true;
		if(str)
		{
			c8* temp = str;
			while(*strToFind)
			{
				if(*strToFind++ != *temp++) result = false;
			}
		}
		return result;
	}

	void strCopy(c8* buffer, const c8* str)
	{
		while (*buffer++ = *str++) {}
	}
	void strnCopy(c8* buffer, u32 num, const c8* str)
	{
		SH_ASSERT(strLength(buffer) >= num);
		num++;
		while((*buffer++ = *str++) && num--) {}
	}

	//TODO replace this with own implementation
	float strToF(c8* str, c8** index)
	{
		return strtof(str, index);
	}

	//TODO replace this with own implementation
	double strToD(c8* str, c8** index)
	{
		return strtod(str, index);
	}
	
}