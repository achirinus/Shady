#include "ImageLoader.h"
#include "ShFile.h"
#include "ComFuncs.h"
#include "stb_image.c"

namespace Shady
{
	
	namespace ImageLoader
	{
		
		Bitmap LoadPngFromFile(String& FileName)
		{
			Bitmap Result{};
			return Result;
		}
		Bitmap LoadFromFile(const String& FileName)
		{
			Bitmap Result{};

			//TODO write my own image loader
			Result.contents = (u32*)stbi_load(FileName.CStr(), (s32*)&Result.width, (s32*)&Result.height, (s32*)&Result.bpp, 4);
			/*
			if (FileName.EndsWith(".png"))
			{
				Result = LoadPngFromFile(FileName);
			}*/
			//TODO implement BMP, JPEG and TGA

			return Result;
		}

		void FreeImage(Bitmap* image)
		{
			if(image) stbi_image_free(image->contents);
			
		}
		
	}
}