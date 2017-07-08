#ifndef SHADY_STRING
#define SHADY_STRING

#include <StringUtils.h>
#include <Commons.h>

namespace Shady
{
		
	class String
	{
	private:
		c8* mBuffer;
		s32 mBufferSize; //this is not the size of string. size of string is mBufferSize - 1;

	public:
		String();
		String(u32 size);
		String(const c8* str);
		String(const String& other);
		String(String&& other);
		String& operator=(const String& other);
		String& operator=(const c8* str);
		~String();
		const c8* cStr() const;
		void reserve(u32 size);
		u32 size() const;
		c8& operator[](s32 index);
		b8 operator==(const String& other);
		b8 cmpIgnoreCase(const String& other);
		String subString(u32 beginIndex, u32 endIndex);
	};
	
}


#endif