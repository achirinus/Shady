#include "Commons.h"
#include <stdarg.h>
#include <Windows.h>
#include "StringUtils.h"

namespace Shady
{

	

	
	
	void customFormat(c8* buffer, u32 bufferSize, const c8* format ...)
	{
		va_list args;
		va_start(args, format);
		c8* tempBuffer = buffer;

		while(*format)
		{
			if(*format == '%')
			{
				if(beginsWith(format+1, "mat4"))
				{

				}
				else if(beginsWith(format+1, "mat3"))
				{
					
				}	
				else if(beginsWith(format+1, "vec4f"))
				{

				}
				else if(beginsWith(format+1, "vec3f"))
				{
					
				}
				else if(beginsWith(format+1, "vec2f"))
				{
					
				}
				else if(beginsWith(format+1, "f32"))
				{
					
				}
				else if(beginsWith(format+1, "s32"))
				{
					
				}			
				else if(beginsWith(format+1, "u32"))
				{
					
				}
				else if(beginsWith(format+1, "f64"))
				{
					
				}
				else if(beginsWith(format+1, "s64"))
				{
					
				}			
				else if(beginsWith(format+1, "u64"))
				{
					
				}
				else if(beginsWith(format+1, "b8"))
				{
					
				}
						
				else if(beginsWith(format+1, "u32"))
				{
					
				}
			}
			else
			{
				*tempBuffer = *format;
			}
			tempBuffer++
			format++;
		}
		*tempBuffer = '\0';
		va_end(args);
		return result;
	}
	
	

	
}

