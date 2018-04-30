#include "ImageLoader.h"
#include "ShFile.h"
#include "ComFuncs.h"

namespace Shady
{
	

	namespace ImageLoader
	{
		
		Bitmap LoadPngFromFile(String& FileName)
		{
			Bitmap Result{};
			return Result;
		}
		Bitmap LoadFromFile(String& FileName)
		{
			Bitmap Result{};

			if (FileName.EndsWith(".png"))
			{
				Result = LoadPngFromFile(FileName);
			}
			//TODO implement BMP, JPEG and TGA

			return Result;
		}

		
	}
}