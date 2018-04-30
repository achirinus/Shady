#ifndef SH_IMAGELOADER_H 
#define SH_IMAGELOADER_H

#include "Bitmap.h"
#include "ShString.h"

namespace Shady
{
	namespace ImageLoader
	{
		Bitmap LoadFromFile(String& FileName);
	}
}

#endif
