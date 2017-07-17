#ifndef SH_BITMAP_H
#define SH_BITMAP_H

namespace Shady
{
	struct Bitmap
	{
		u32* contents;
		u32 width;
		u32 height;
		u32 bpp;
		u32 pitch;
		u32 totalSize;
	};
}

#endif