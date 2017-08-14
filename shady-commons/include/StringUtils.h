#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "ShadyTypes.h"
#include "ShadyAssert.h"
#include <cstdarg>

namespace Shady
{
	c8* skipChars(c8* str, c8 c);
	c8* findChar(c8* str, c8 c);
	c8* findStr(c8* str, c8* strToFind);
	const c8* findFirstDigit(const c8* str);
	c8* findFirstDigit(c8* str);
	c8* strConcat(const c8* first, const c8* second);
	c8* s32ToStr(s32 num);
	void s32ToStr(c8* buffer, u32 bufferSize, s32 num);
	s64 strTos64(c8* str);
	s32 strTos32(c8* str);
	u64 strTou64(c8* str);
	u32 strTou32(c8* str);
	f32 strTof32(c8* str, c8** index = 0);
	f64 strTof64(c8* str, c8** index = 0);
	s32 charToDigit(c8 c);
	u32 digitCount(s32 num, s32 base);
	b8 strCompare(const c8* str1, const c8* str2);
	b8 strCompare(const c16* str1, const c16* str2);
	b8 strCompareNoCase(const c8* str1, const c8* str2);
	b8 charCompareNoCase(c8 c1, c8 c2);
	u32 strLength(const c8 *str);
	u32 strLength(const c16 *str);
	b8 isLetter(c8 c);
	b8 isDigit(c8 c);
	s32 getLine(c8* buffer, s32 bufferLength, c8* str);
	b8 endsWith(c8* str, c8* end);
	b8 beginsWith(const c8* str, const c8* strToFind);
	void strCopy(c8* buffer, const c8* str);
	void strnCopy(c8* buffer, u32 num, const c8* str);
	void customFormat(c8* buffer, const c8* format ...);
}

#endif


