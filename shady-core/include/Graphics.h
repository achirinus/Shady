#ifndef SH_GRAPHICS_H
#define SH_GRAPHICS_H


#include "ShadyTypes.h"
#include "FileUtils.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include "Bitmap.h"

class Texture;

namespace Shady
{
	void freeBitmap(Bitmap bitmap);
	Bitmap createEmptyBitmap(u32 width, u32 height, u32 bpp, b8 clearToZero = true);
	Bitmap get32bppBitmapFrom8bpp(u8* contents, u32 width, u32 height);

}

#endif
