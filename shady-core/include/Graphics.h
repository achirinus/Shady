#ifndef SH_GRAPHICS_H
#define SH_GRAPHICS_H


#include "ShadyTypes.h"
#include "FileUtils.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include "Bitmap.h"
#include "Texture.h"



namespace Shady
{
	Texture* getGlyphTexture(c8 glyph, f32 pixelSize);
	void freeBitmap(Bitmap bitmap);
	Bitmap createEmptyBitmap(u32 width, u32 height, u32 bpp, b8 clearToZero = true);
	Bitmap get32bppBitmapFrom8bpp(u8* contents, u32 width, u32 height);

}

#endif
