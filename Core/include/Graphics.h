#ifndef SH_GRAPHICS_H
#define SH_GRAPHICS_H


#include "ShTypes.h"
#include "ShFile.h"
#include "Bitmap.h"
#include "Texture.h"



namespace Shady
{
	
	void freeBitmap(Bitmap bitmap);
	Bitmap createEmptyBitmap(u32 width, u32 height, u32 bpp, b8 clearToZero = true);
	Bitmap get32bppBitmapFrom8bpp(u8* contents, u32 width, u32 height);
	void BlitRectInBitmap(u32* sBuf, u32 sWidth, u32 sHeight, u32 dx, u32 dy, u32* dBuf, u32 dWidth, u32 dHeight);

}

#endif
