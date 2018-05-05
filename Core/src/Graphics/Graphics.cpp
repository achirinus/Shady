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
		if (!size) return result;
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

	void BlitRectInBitmap(u32* sBuf, u32 sWidth, u32 sHeight, u32 dx, u32 dy, u32* dBuf, u32 dWidth, u32 dHeight)
	{
		if (!sBuf || !sWidth || !sHeight) return;
		if ((dx + sWidth) > dWidth) return;
		if ((dy + sHeight) > dHeight) return;
		u32 tempX = dx;
		for (u32 ys = 0; ys < sHeight; ++ys)
		{
			for (u32 xs = 0; xs < sWidth; ++xs)
			{
				dBuf[dy * dWidth + dx++] = sBuf[ys * sWidth + xs];
			}
			dx = tempX;
			++dy;
		}
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