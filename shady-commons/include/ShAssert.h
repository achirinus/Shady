#ifndef SH_ASSERT_H
#define SH_ASSERT_H

#include "ShTypes.h"
#include "Windows.h"
namespace Shady
{
	//TODO upgrade this sometime to show file, line etc
	void _sh_crazy_assert(bool cond);
	void _sh_chill_assert(bool cond, const char* str, ...);
	void _HandleAssertBox(const c8* mes);
	#if defined (SHADY_DEBUG) || (SHADY_DEBUG_RELEASE)
		#if defined (_MSC_VER)
			#define DEBUG_BREAK __debugbreak()
		#else
			//TODO break for other platforms/compilers
			#define DEBUG_BREAK
		#endif

		#define SH_CHILL_ASSERT(exp, str, ...) _sh_chill_assert(exp, str, __VA_ARGS__)
		#define SH_ASSERT(exp, ...) if (!(exp)) 															      \
									{																			  \
										const c8* mes = "Assertion(" #exp ") failed in function: \n" __FUNCSIG__;  \
										_HandleAssertBox(mes);													  \
									}

		#define INVALID_CODE_PATH SH_ASSERT(false)
	#else
		#define DEBUG_BREAK
		#define SH_ASSERT(exp, ...)
		#define INVALID_CODE_PATH
	#endif
}

#endif