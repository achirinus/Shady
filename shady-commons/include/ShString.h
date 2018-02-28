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

		void InitBuffer(u32 size);
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
		const c8* CStr() const;
		void Reserve(u32 size);
		u32 Size() const;
		c8& operator[](s32 index);
		b8 operator==(const String& other) const;
		b8 operator!=(const String& other) const;
		String operator+(const c8* str);
		String operator+(const c8 c);
		String operator+(s32 num);
		String operator+(const String& other);
		String& operator+=(const c8* str);
		String& operator+=(const c8 c);
		String& operator+=(const String& other);
		c8* operator*();
		const c8* operator*() const;
		operator b8();
		b8 CmpIgnoreCase(const String& other);
		String SubString(u32 beginIndex, u32 numOfElem);
		Array<String> Split(c8 token);
		f32 Tof32();
		f64 Tof64();
		s32 Tos32();
		String GetLine();
		b8 BeginsWith(c8 character);
		b8 BeginsWith(const char* str);
		static String FormatString(const char* format, ...);
		static String FormatString(String format, ...);
	};
	
}


#endif