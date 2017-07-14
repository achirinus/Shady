#include "Graphics.h"


namespace Shady
{

	void clearBitmapToZero(Bitmap* bmp)
	{
		if(bmp->contents)
		{
			u32* mem = bmp->contents;
			for(u32 x = 0; x < bmp->totalSize; x++)
			{
				*mem++ = 0;
			}
		}
	}
	Bitmap createEmptyBitmap(u32 width, u32 height, u32 bpp, b8 clearToZero)
	{
		Bitmap result{};

		u32 size = width * height * bpp;
		SH_ASSERT(size);
		result.contents = new u32[size];
		result.bpp = bpp;
		result.totalSize = size;
		result.pitch = width * bpp;
		result.width = width;
		result.height = height;

		if(clearToZero)
		{
			clearBitmapToZero(&result);
		}
		return result;
	}

	void freeBitmap(Bitmap bitmap)
	{
		delete[] bitmap.contents;
	}

	Bitmap get32bppBitmapFrom8bpp(u8* contents, u32 width, u32 height)
	{
		Bitmap result = createEmptyBitmap(width, height, 4);
		u8* source = contents;
		u32* dest = result.contents;
		
		u8* row = (u8*)result.contents;
		for(u32 y = 0; y < height; y++)
		{
			u32* dest = (u32*)row;
			for(u32 x = 0; x < width; x++)
			{
				u8 data = *source++;
				*dest++ = ((data << 24) |
						(data << 16) |
						(data << 8) |
						(data << 0));
			}

			row += result.pitch;
		}

		/*
		u32 bmpSize = width * height;
		for(u32 index = 0; index < width * height; index++)
		{
			u8 value = *source++;
			*dest++ = ((value << 24) |
						(value << 16) |
						(value << 8) |
						(value << 0));
		}
		*/
		return result;
	}
	
}