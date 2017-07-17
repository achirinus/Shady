#ifndef SH_TYPES_H
#define SH_TYPES_H

namespace Shady
{
	#ifdef WIN32
		#ifdef  _MSC_VER
			typedef char c8;
			typedef unsigned char uc8;
			typedef unsigned char u8;
			typedef wchar_t c16;
			typedef int c32;
			typedef bool b8;
			typedef short s16;
			typedef unsigned short u16;
			typedef int b32;
			typedef int s32;
			typedef unsigned int u32;
			typedef long long s64;
			typedef unsigned long long u64;
			typedef float f32;
			typedef double f64;
			typedef int int32;
			typedef long long int64;
			typedef char int8;
			typedef short int16;
			typedef unsigned int uint32;
			typedef unsigned long long uint64;
			typedef unsigned char uint8;
			typedef unsigned short uint16;

			typedef float float32;
			typedef double float64;

			#define C8_MIN (-128)
			#define C8_MAX (127)
			#define C16_MIN (-32768)
			#define C16_MAX	(32767)
			#define C32_MIN (-2147483648)
			#define C32_MAX (2147483647)
			#define U8_MAX (255)
			#define U16_MAX (65535)
			#define U32_MAX (4294967295)
			#define U64_MAX (18446744073709551615)
			#define S8_MIN (-128)
			#define S8_MAX (127)
			#define S16_MIN (-32768)
			#define S16_MAX (32767)
			#define S32_MIN (-2147483648)
			#define S32_MAX (2147483647)
			#define S64_MIN (-9223372036854775808)
			#define S64_MAX (9223372036854775807)
		#endif // _MSC_VER
	#endif //WIN32
	
}


#endif