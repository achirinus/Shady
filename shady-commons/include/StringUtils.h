#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "ShTypes.h"
#include "ShAssert.h"
#include <cstdarg>

namespace Shady
{
	c8* SkipChars(c8* str, c8 c);
	c8* FindChar(c8* str, c8 c);
	c8* FindStr(c8* str, c8* strToFind);
	const c8* FindFirstDigit(const c8* str);
	c8* FindFirstDigit(c8* str);
	c8* StrConcat(const c8* first, const c8* second);
	c8* S32ToStr(s32 num);
	void S32ToStr(c8* buffer, u32 bufferSize, s32 num);
	s64 StrTos64(c8* str);
	s32 StrTos32(c8* str);
	u64 StrTou64(c8* str);
	u32 StrTou32(c8* str);
	f32 StrTof32(c8* str, c8** index = 0);
	f64 StrTof64(c8* str, c8** index = 0);
	s32 CharToDigit(c8 c);
	u32 DigitCount(s32 num, s32 base = 10);
	b8 StrCompare(const c8* str1, const c8* str2);
	b8 StrCompare(const c16* str1, const c16* str2);
	b8 StrCompareNoCase(const c8* str1, const c8* str2);
	b8 CharCompareNoCase(c8 c1, c8 c2);
	u32 StrLength(const c8 *str);
	u32 StrLength(const c16 *str);
	b8 IsLetter(c8 c);
	b8 IsDigit(c8 c);
	s32 GetLine(c8* buffer, s32 bufferLength, c8* str);
	b8 EndsWith(c8* str, c8* end);
	b8 BeginsWith(const c8* str, const c8* strToFind);
	void StrCopy(c8* buffer, const c8* str);
	void StrnCopy(c8* buffer, u32 num, const c8* str);
	s32 StrCopyNoTerminator(c8* buffer, const c8* str);
	void CustomFormat(c8* buffer, const c8* format ...);
}

#endif



