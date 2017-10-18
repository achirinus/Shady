#ifndef SHADY_STRING
#define SHADY_STRING

#include <StringUtils.h>
#include <Commons.h>
#include <ShArray.h>
#include <initializer_list>

namespace Shady
{
	#define SH_STRING_ENDED "SHADY_STRING_ENDED"
	class String
	{
	private:
		c8* mBuffer;
		s32 mBufferSize; //this is not the size of string. size of string is mBufferSize - 1;

	public:
		String();
		String(std::initializer_list<const char*> list);
		String(u32 integer);
		String(const c8* str);
		String(const String& other);
		String(String&& other);
		String(s32 numOfStrings, ...);
		String& operator=(const String& other);
		String& operator=(const c8* str);
		~String();
		const c8* cStr() const;
		void reserve(u32 size);
		u32 size() const;
		c8& operator[](s32 index);
		b8 operator==(const String& other);
		b8 operator!=(const String& other);
		String operator+(const c8* str);
		String operator+(const String& other);
		String& operator+=(const c8* str);
		String& operator+=(const String& other);
		b8 cmpIgnoreCase(const String& other);
		String subString(u32 beginIndex, u32 numOfElem);
		Array<String> split(c8 token);
		f32 tof32();
		f64 tof64();
		s32 tos32();
		String getLine();
		b8 beginsWith(c8 character);
		b8 beginsWith(const char* str);
	};
	
}


#endif