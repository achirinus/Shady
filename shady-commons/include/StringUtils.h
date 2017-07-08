#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <Commons.h>

namespace Shady
{
	
	c8* findChar(c8* str, c8 c);
	c8* findStr(c8* str, c8* strToFind);
	b8 strCompare(const c8* str1, const c8* str2);
	b8 strCompare(const c16* str1, const c16* str2);
	b8 strCompareNoCase(const c8* str1, const c8* str2);
	u32 strLength(const c8 *str);
	u32 strLength(const c16 *str);
	b8 isLetter(c8 c);
	b8 cmpCharsNoCase(c8 c1, b8 c2);
	int getLine(c8* buffer, int bufferLength, c8* str);
	bool endsWith(c8* str, c8* end);
	void strCopy(c8* buffer, const c8* str);
	void strnCopy(c8* buffer, const c8* str);
	float strToF(c8* str, c8** index = 0);
}

#endif


