#include "StringUtils.h"
#include "ShMath.h"



namespace Shady
{
	c8 base2Digits[] = "01";
	c8 base10Digits[] = "0123456789";
	c8 base16DigitsUpper[] = "0123456789ABCDEF";
	c8 base16DigitsLower[] = "0123456789abcdef";

	c8* skipChars(c8* str, c8 c)
	{
		while(*str && (*str == c)) str++;
		return str;
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

	c8* findStr(c8* str, c8* strToFind)
	{
		bool found = false;
		c8* value = nullptr;
		c8* tempStr = str;
		while (*tempStr != '\0')
		{
			if (*tempStr == *strToFind)
			{
				found = true;
				c8* potetialWinner = tempStr;
				c8* tempStrToFind = strToFind;
				while (*tempStrToFind != '\0')
				{
					if (*tempStr == '\0') return value;
					if (*tempStrToFind != *tempStr) 
					{
						found = false;
						break;
					}
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

	const c8* findFirstDigit(const c8* str)
	{
		while(*str)
		{
			if(isDigit(*str)) return str;
			str++;
		}
		return 0;
	}

	c8* findFirstDigit(c8* str)
	{
		while(*str)
		{
			if(isDigit(*str)) return str;
			str++;
		}
		return 0;
	}

	c8* strConcat(const c8* first, const c8* second)
	{
		u32 firstLen = strLength(first);
		u32 secondLen = strLength(second);
		c8* result = new c8[firstLen + secondLen + 1];
		c8* temp = result;
		strCopy(temp, first);
		temp+= firstLen;
		strCopy(temp, second);
		temp+= secondLen;
		*temp = '\0';
		return result;
	}

	c8* s32ToStr(s32 num)
	{
		c8* result = new c8[S32_CHAR_NUM + 1];
		s32ToStr(result, S32_CHAR_NUM + 1, num);
		return result;
	}

	void s32ToStr(c8* buffer, u32 bufferSize, s32 num)
	{
		SH_ASSERT(buffer);
		SH_ASSERT(bufferSize);

		c8 temp[S32_CHAR_NUM + 1];
		u32 numbersRead = 0;
		b8 isNegative = (num < 0);
		if(isNegative) num = -num;
		
		do
		{
			temp[numbersRead++] = num % 10;
			num /= 10;
		} while(num);
		u32 counter = 0;

		if(isNegative) buffer[counter++] = '-';

		while(numbersRead)
		{
			if(counter < bufferSize - 1)
			{
				buffer[counter++] = base10Digits[temp[--numbersRead]];
			}
			else
			{
				break;
			}
		}
		buffer[counter] = 0;
	}

	s64 strTos64(c8* str)
	{
		s64 result = 0;
		b8 digitStarted = false;
		b8 isNegative = false;
		while(*str)
		{
			if(!isDigit(*str))
			{
				if(digitStarted) break;
				if(*str != '-')
				{
					str++;
				}
				else
				{
					if(isDigit(*++str))
					{
						isNegative = true;
						digitStarted = true;	
					}
				} 
			}
			else //is Digit
			{
				digitStarted = true;
				result *= 10;
				result += *str++ - '0';
			}
		}
		if(isNegative) result = -result;
		return result;
	}

	s32 strTos32(c8* str)
	{
		return (s32)strTos64(str);
	}

	u64 strTou64(c8* str)
	{
		SH_ASSERT(str);
		u64 result = 0;
		b8 digitStarted = false;
		while(*str)
		{
			if(!isDigit(*str))
			{
				if(digitStarted) break;
				str++;
			}
			else //is Digit
			{
				digitStarted = true;
				result *= 10;
				result += *str++ - '0';
			}
		}
		SH_ASSERT(digitStarted); 

		return result;
	}

	u32 strTou32(c8* str)
	{
		return (u32)strTou64(str);
	}

	//TODO replace this with own implementation
	float strTof32(c8* str, c8** index)
	{
		return strtof(str, index);
	}

	//TODO replace this with own implementation
	double strTof64(c8* str, c8** index)
	{
		return strtod(str, index);
	}

	s32 charToDigit(c8 c)
	{
		s32 result = INVALID_DIGIT;
		if(isDigit(c)) result = (c - '0');
		return result;
	}

	u32 digitCount(s32 num, s32 base)
	{
		u32 result = 0;
		b8 isNegative = (num < 0);
		
		if(isNegative) num = - num;
		do
		{	
			result++;
			num /= base;
		}while(num);

		return result;
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
			if (!charCompareNoCase(*str1, *str2)) return false;
			str1++;
			str2++;
		}

		return true;
	}

	b8 charCompareNoCase(c8 c1, c8 c2)
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

	u32 strLength(const c8 *str)
	{
		u32 result = 0;
		if(str)
		{
			while (*str++) result++;	
		}
		
		return result;
	}
	
	u32 strLength(const c16 *str)
	{
		u32 result = 0;
		while (*str++) result++;

		return result;
	}

	b8 isLetter(c8 c)
	{
		return ((c > 64) && (c < 91)) || ((c > 96) && (c < 123));
	}

	b8 isDigit(c8 c)
	{
		return ((c >= '0') &&(c <= '9'));
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
			const c8* temp = str;
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

	s32 strCopyNoTerminator(c8* buffer, const c8* str)
	{
		s32 result = 0;
		while(*str)
		{
			*buffer++ = *str++;
			result++;
		}
		return result;
	}
	void strnCopy(c8* buffer, u32 num, const c8* str)
	{
		SH_ASSERT(buffer);
		while(num-- && (*buffer++ = *str++)) {}
		*buffer = 0;
	}

	void customFormat(c8* buffer, const c8* format, va_list args)
	{
		c8* tempBuffer = buffer;

		while(*format)
		{
			if(*format == '%')
			{
				if(beginsWith(format+1, "mat4"))
				{
					c8 tb[256];
					c8* tbp = &tb[0]; 
					Matrix4f mat = va_arg(args, Matrix4f);
					sprintf_s(tb, 256, "%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
										mat.elem[0], mat.elem[1], mat.elem[2], mat.elem[3],
										mat.elem[4], mat.elem[5], mat.elem[6], mat.elem[7], 
										mat.elem[8], mat.elem[9], mat.elem[10], mat.elem[11],
										mat.elem[12], mat.elem[13], mat.elem[14], mat.elem[15]);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=5;
					continue;
				}
				else if(beginsWith(format+1, "mat3"))
				{
					c8 tb[256];
					c8* tbp = &tb[0];
					Matrix3f mat = va_arg(args, Matrix3f);
					sprintf_s(tb, 256, "%f %f %f\n%f %f %f\n%f %f %f\n",
										mat.elem[0], mat.elem[1], mat.elem[2],
										mat.elem[3], mat.elem[4], mat.elem[5],
										mat.elem[6], mat.elem[7], mat.elem[8]);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=5;
					continue;

				}	
				else if(beginsWith(format+1, "vec4f"))
				{
					c8 tb[128];
					c8* tbp = &tb[0];
					Vec4f vec = va_arg(args, Vec4f);
					sprintf_s(tb, 128, "|%f %f %f %f|", vec.x, vec.y, vec.z, vec.w);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=6;
					continue;
				}
				else if(beginsWith(format+1, "vec3f"))
				{
					c8 tb[128];
					c8* tbp = &tb[0];
					Vec3f vec = va_arg(args, Vec3f);
					sprintf_s(tb, 128, "|%f %f %f|", vec.x, vec.y, vec.z);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=6;
					continue;
				}
				else if(beginsWith(format+1, "vec2f"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					Vec2f vec = va_arg(args, Vec2f);
					sprintf_s(tb, 48, "|%f %f|", vec.x, vec.y);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=6;
					continue;
				}
				else if(beginsWith(format+1, "f32"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					f64 num = va_arg(args, f64);
					sprintf_s(tb, 48, "%f", num);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=4;
					continue;
				}
				else if(beginsWith(format+1, "s32"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					s32 num = va_arg(args, s32);
					sprintf_s(tb, 48, "%d", num);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=4;
					continue;
				}			
				else if(beginsWith(format+1, "u32"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					u32 num = va_arg(args, u32);
					sprintf_s(tb, 48, "%u", num);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=4;
					continue;
				}
				else if(beginsWith(format+1, "f64"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					f64 num = va_arg(args, f64);
					sprintf_s(tb, 48, "%f", num);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=4;
					continue;
				}
				else if(beginsWith(format+1, "s64"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					s64 num = va_arg(args, s64);
					sprintf_s(tb, 48, "%lld", num);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=4;
					continue;
				}			
				else if(beginsWith(format+1, "u64"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					u64 num = va_arg(args, u64);
					sprintf_s(tb, 48, "%llu", num);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=4;
					continue;
				}
				else if(beginsWith(format+1, "b8"))
				{
					c8 tb[8];
					c8* tbp = &tb[0];
					b8 num = va_arg(args, b8);
					if(!num)
					{
						sprintf_s(tb, 8, "FALSE");
					}
					else
					{
						sprintf_s(tb, 8, "TRUE");
					}
					
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=3;
					continue;
				}
				else if(beginsWith(format+1, "str"))
				{
					String str = va_arg(args, String);
					const c8* tempStr = str.cStr();
					u32 tbSize = str.size();
					while(tbSize--)
					{
						*tempBuffer++ = *tempStr++;
					}
					format+=4;
					continue;
				}
				else if(beginsWith(format+1, "s"))
				{
					c8* tempStr = va_arg(args, c8*);
					
					u32 tbSize = strLength(tempStr);
					while(tbSize--)
					{
						*tempBuffer++ = *tempStr++;
					}
					format+=2;
					continue;
				}
				else if(beginsWith(format + 1, "c8"))
				{
					c8 tb[4];
					c8* tbp = &tb[0];
					s32 c = va_arg(args, s32);
					sprintf_s(tb, 4, "%c", c);
					u32 tbSize = strLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format += 3;
					continue;
				}
				
			}
			else
			{
				*tempBuffer = *format;
			}
			tempBuffer++;
			format++;
		}
		*tempBuffer = '\0';
	}
	
	void customFormat(c8* buffer, const c8* format ...)
	{
		va_list args;
		va_start(args, format);
		customFormat(buffer, format, args);
		va_end(args);
		
	}

	void toAllCaps(c8* str)
	{
		while(*str)
		{
			if((*str >= 'a') && (*str <= 'z')) *str -= 32;
			str++;
		}
	}

	void toAllLower(c8* str)
	{
		while(*str)
		{
			if((*str >= 'A') && (*str <= 'Z')) *str += 32;
			str++;
		}
	}
	
}