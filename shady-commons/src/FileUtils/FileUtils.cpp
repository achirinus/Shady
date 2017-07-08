#include "FileUtils.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <string>

#pragma warning(disable:4996)

namespace Shady
{
	
		namespace File
		{
			uint64 getSize(const char* fileName)
			{
				uint64 size = 0;
				FILE* file = fopen(fileName, "r");
				if (file)
				{
					fseek(file, 0, SEEK_END);
					size = ftell(file);
					fclose(file);
				}

				return size;
			}


			char* readTextFile(const char* fileName)
			{
				char* contents = nullptr;
				std::ifstream file(fileName);
				if (file)
				{

					file.seekg(0, file.end);
					u32 size = (u32)file.tellg();
					file.seekg(0, file.beg);

					contents = new char[size + 1];
					file.get(contents, size + 1, NULL);
				}
				return contents;
			}


			float stof(const char* s) {
				float rez = 0, fact = 1;
				if (*s == '-') {
					s++;
					fact = -1;
				};
				for (int point_seen = 0; *s; s++) {
					if (*s == '.') {
						point_seen = 1;
						continue;
					};
					int d = *s - '0';
					if (d >= 0 && d <= 9) {
						if (point_seen) fact /= 10.0f;
						rez = rez * 10.0f + (float)d;
					};
				};
				return rez * fact;
			};

		}
	
}