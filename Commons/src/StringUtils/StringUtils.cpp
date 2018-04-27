#include "StringUtils.h"
#include "ShMath.h"



namespace Shady
{
	c8 base2Digits[] = "01";
	c8 base10Digits[] = "0123456789";
	c8 base16DigitsUpper[] = "0123456789ABCDEF";
	c8 base16DigitsLower[] = "0123456789abcdef";

	//Skips contiguous chars from the beggining of the string str
	c8* SkipFirstChars(c8* str, const c8 c)
	{
		if(str)
		{
			while(*str &&(*str == c)) str++;
		}
		return str;
	}

	c8* FindChar(c8* str, c8 c)
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

	c8* FindStr(c8* str, const c8* strToFind)
	{
		bool found = false;
		c8* value = nullptr;
		c8* tempStr = str;
		if (!tempStr) return 0;
		while (*tempStr != '\0')
		{
			if (*tempStr == *strToFind)
			{
				found = true;
				c8* potetialWinner = tempStr;
				const c8* tempStrToFind = strToFind;
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

	const c8* FindFirstDigit(const c8* str)
	{
		while(*str)
		{
			if(IsDigit(*str)) return str;
			str++;
		}
		return 0;
	}

	c8* FindFirstDigit(c8* str)
	{
		while(*str)
		{
			if(IsDigit(*str)) return str;
			str++;
		}
		return 0;
	}

	c8* StrConcat(const c8* first, const c8* second)
	{
		u32 firstLen = StrLength(first);
		u32 secondLen = StrLength(second);
		c8* result = new c8[firstLen + secondLen + 1];
		c8* temp = result;
		StrCopy(temp, first);
		temp+= firstLen;
		StrCopy(temp, second);
		temp+= secondLen;
		*temp = '\0';
		return result;
	}

	c8* S32ToStr(s32 num)
	{
		c8* result = new c8[S32_CHAR_NUM + 1];
		S32ToStr(result, S32_CHAR_NUM + 1, num);
		return result;
	}

	void S32ToStr(c8* buffer, u32 bufferSize, s32 num)
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

	s64 StrTos64(c8* str)
	{
		s64 result = 0;
		b8 digitStarted = false;
		b8 isNegative = false;
		while(*str)
		{
			if(!IsDigit(*str))
			{
				if(digitStarted) break;
				if(*str != '-')
				{
					str++;
				}
				else
				{
					if(IsDigit(*++str))
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

	s32 StrTos32(c8* str)
	{
		return (s32)StrTos64(str);
	}

	u64 StrTou64(c8* str)
	{
		SH_ASSERT(str);
		u64 result = 0;
		b8 digitStarted = false;
		while(*str)
		{
			if(!IsDigit(*str))
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

	u32 StrTou32(c8* str)
	{
		return (u32)StrTou64(str);
	}

	//TODO replace this with own implementation
	float StrTof32(c8* str, c8** index)
	{
		return strtof(str, index);
	}

	//TODO replace this with own implementation
	double StrTof64(c8* str, c8** index)
	{
		return strtod(str, index);
	}

	s32 CharToDigit(c8 c)
	{
		s32 result = INVALID_DIGIT;
		if(IsDigit(c)) result = (c - '0');
		return result;
	}

	u32 DigitCount(s32 num, s32 base)
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

	
	bool StrCompare(const c8* str1, const c8* str2)
	{
		
		if (StrLength(str1) != StrLength(str2)) return false;
		
		while (*str1)
		{
			if (*str1 != *str2) return false;
			str1++;
			str2++;
		}
		return true;
	}

	b8 StrCompare(const c16* str1, const c16* str2)
	{
		if (StrLength(str1) != StrLength(str2)) return false;
		
		while (*str1)
		{
			if (*str1 != *str2) return false;
			str1++;
			str2++;
		}
		return true;
	}

	bool StrCompareNoCase(const c8* str1, const c8* str2)
	{
		if (StrLength(str1) != StrLength(str2)) return false;
		while (*str1 || *str2)
		{
			if (!CharCompareNoCase(*str1, *str2)) return false;
			str1++;
			str2++;
		}

		return true;
	}

	b8 CharCompareNoCase(c8 c1, c8 c2)
	{
		if (IsLetter(c1) && IsLetter(c2))
		{
			s32 dif = Absolute(c1 - c2);
			if ((dif == 32) || (dif == 0)) return true;

			return false;
		}
		else if (c1 == c2) return true;
		return false;
	}

	u32 StrLength(const c8 *str)
	{
		u32 result = 0;
		if(str)
		{
			while (*str++) result++;	
		}
		return result;
	}
	
	u32 StrLength(const c16 *str)
	{
		u32 result = 0;
		if(str)
		{
			while (*str++) result++;	
		}
		return result;
	}

	b8 IsLetter(c8 c)
	{
		return ((c > 64) && (c < 91)) || ((c > 96) && (c < 123));
	}

	b8 IsDigit(c8 c)
	{
		return ((c >= '0') &&(c <= '9'));
	}

	
	
	int GetLine(c8* buffer, int bufferLength, c8* str)
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

	bool EndsWith(c8* str, c8* end)
	{
		u32 sizeStr = StrLength(str);
		u32 sizeEnd = StrLength(end);
		if(sizeEnd > sizeStr) return false;
		bool result = StrCompare((str + (sizeStr - sizeEnd)), end);

		return result;
	}

	bool BeginsWith(const c8* str, const c8* strToFind)
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

	s32 StrCopy(c8* buffer, const c8* str)
	{
		s32 result = 0;
		if (str)
		{
			while (*buffer++ = *str++) { result++; }
		}
		return result;
	}
	void StrnCopy(c8* buffer, u32 num, const c8* str)
	{
		if (!buffer) return;
		if (!num) return;
		if (!str) return;
		while(num-- && (*buffer++ = *str++)) {}
		*buffer = 0;
	}

	void StrnCopyNoTerminator(c8* buffer, u32 num, const c8* str)
	{
		if (!buffer) return;
		if (!num) return;
		if (!str) return;
		while (num-- && (*buffer++ = *str++)) {}
		
	}

	s32 StrCopyNoTerminator(c8* buffer, const c8* str)
	{
		s32 result = 0;
		while(*str)
		{
			*buffer++ = *str++;
			result++;
		}
		return result;
	}

	void CustomFormat(c8* buffer, const c8* format ...)
	{
		va_list args;
		va_start(args, format);
		CustomFormatVar(buffer, format, args);
		va_end(args);
	}
	
	//TODO replace sprintf_s with my own
	void CustomFormatVar(c8* buffer, const c8* format, va_list args)
	{
		c8* tempBuffer = buffer;

		while(*format)
		{
			if(*format == '%')
			{
				b8 op1 = false;
				if((op1 = BeginsWith(format+1, "mat4")) || BeginsWith(format+1, "m4"))
				{
					c8 tb[256];
					c8* tbp = &tb[0]; 
					Matrix4f mat = va_arg(args, Matrix4f);
					sprintf_s(tb, 256, "%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
										mat.elem[0], mat.elem[1], mat.elem[2], mat.elem[3],
										mat.elem[4], mat.elem[5], mat.elem[6], mat.elem[7], 
										mat.elem[8], mat.elem[9], mat.elem[10], mat.elem[11],
										mat.elem[12], mat.elem[13], mat.elem[14], mat.elem[15]);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+= op1 ? 5 : 3;
					continue;
				}
				else if((op1 = BeginsWith(format+1, "mat3")) || BeginsWith(format+1, "m3"))
				{
					c8 tb[256];
					c8* tbp = &tb[0];
					Matrix3f mat = va_arg(args, Matrix3f);
					sprintf_s(tb, 256, "%f %f %f\n%f %f %f\n%f %f %f\n",
										mat.elem[0], mat.elem[1], mat.elem[2],
										mat.elem[3], mat.elem[4], mat.elem[5],
										mat.elem[6], mat.elem[7], mat.elem[8]);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+= op1 ? 5 : 3;
					continue;

				}	
				else if((op1 = BeginsWith(format+1, "vec4f")) || BeginsWith(format+1, "v4"))
				{
					c8 tb[128];
					c8* tbp = &tb[0];
					Vec4f vec = va_arg(args, Vec4f);
					sprintf_s(tb, 128, "{%f %f %f %f}", vec.x, vec.y, vec.z, vec.w);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+= op1 ? 6 : 3;
					continue;
				}
				else if((op1 = BeginsWith(format+1, "vec3f")) || BeginsWith(format+1, "v3"))
				{
					c8 tb[128];
					c8* tbp = &tb[0];
					Vec3f vec = va_arg(args, Vec3f);
					sprintf_s(tb, 128, "{%f %f %f}", vec.x, vec.y, vec.z);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+= op1 ? 6 : 3;
					continue;
				}
				else if((op1 = BeginsWith(format+1, "vec2f")) || BeginsWith(format+1, "v2"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					Vec2f vec = va_arg(args, Vec2f);
					sprintf_s(tb, 48, "{%f %f}", vec.x, vec.y);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+= op1 ? 6 : 3;
					continue;
				}
				else if((op1 = BeginsWith(format+1, "f32")) || BeginsWith(format+1, "f"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					// This is not wrong!!!!!! 
					// 32 bit floats are saved as 64 bit in varargs, so if you get just 32 bits from that, 
					// you brake it and everything after it
					f64 num = va_arg(args, f64); 
					sprintf_s(tb, 48, "%f", num);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+= op1 ? 4 : 2;
					continue;
				}
				else if((op1 = BeginsWith(format+1, "s32")) || BeginsWith(format+1, "d"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					s32 num = va_arg(args, s32);
					sprintf_s(tb, 48, "%d", num);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+= op1 ? 4 : 2;
					continue;
				}			
				else if((op1 = BeginsWith(format+1, "u32")) || BeginsWith(format+1, "u"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					u32 num = va_arg(args, u32);
					sprintf_s(tb, 48, "%u", num);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+= op1 ? 4 : 2;
					continue;
				}
				else if(BeginsWith(format+1, "f64"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					f64 num = va_arg(args, f64);
					sprintf_s(tb, 48, "%f", num);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=4;
					continue;
				}
				else if(BeginsWith(format+1, "s64") || BeginsWith(format+1, "lld"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					s64 num = va_arg(args, s64);
					sprintf_s(tb, 48, "%lld", num);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+= 4;
					continue;
				}			
				else if(BeginsWith(format+1, "u64") || BeginsWith(format+1, "llu"))
				{
					c8 tb[48];
					c8* tbp = &tb[0];
					u64 num = va_arg(args, u64);
					sprintf_s(tb, 48, "%llu", num);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=4;
					continue;
				}
				else if(BeginsWith(format+1, "b8"))
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
					
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+=3;
					continue;
				}
				else if(BeginsWith(format+1, "str"))
				{
					String str = va_arg(args, String);
					const c8* tempStr = str.CStr();
					u32 tbSize = str.Size();
					while(tbSize--)
					{
						*tempBuffer++ = *tempStr++;
					}
					format+=4;
					continue;
				}
				else if(BeginsWith(format+1, "s"))
				{
					c8* tempStr = va_arg(args, c8*);
					u32 tbSize = StrLength(tempStr);
					while(tbSize--)
					{
						*tempBuffer++ = *tempStr++;
					}
					format+=2;
					continue;
				}
				else if((op1 = BeginsWith(format + 1, "c8")) || BeginsWith(format + 1, "c"))
				{
					c8 tb[4];
					c8* tbp = &tb[0];
					s32 c = va_arg(args, s32);
					sprintf_s(tb, 4, "%c", c);
					u32 tbSize = StrLength(tb);
					while(tbSize--)
					{
						*tempBuffer++ = *tbp++;
					}
					format+= op1 ? 3 : 2;
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
	
}