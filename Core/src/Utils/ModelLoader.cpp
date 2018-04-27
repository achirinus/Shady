#include "ModelLoader.h"
#include "Commons.h"

namespace Shady
{
	Mesh* ModelLoader::loadObj(const char* fileName)
	{
		
		String fileContent = File::ReadTextFile(fileName);
		String line;
		Array<Vertex> vertices{};
		Array<Vec4f> pos{};
		Array<Vec3f> norm{};
		Array<Vec2f> texCoord{};
		
 		while( line = fileContent.GetLine(), line!=SH_STRING_ENDED)
		{
			if(line.BeginsWith("vn"))
			{
				Array<String> chunks = line.Split(' ');
				if(chunks.Size() == 4)
				{
					norm.Add({chunks[1].Tof32(), chunks[2].Tof32(), chunks[3].Tof32()});
				}
			}
			else if(line.BeginsWith("vt"))
			{
				Array<String> chunks = line.Split(' ');
				if(chunks.Size() == 3)
				{
					texCoord.Add({chunks[1].Tof32(), chunks[2].Tof32()});
				}
			}
			else if(line.BeginsWith('v'))
			{
				Array<String> chunks = line.Split(' ');
				if(chunks.Size() == 4)
				{
					pos.Add({chunks[1].Tof32(), chunks[2].Tof32(), chunks[3].Tof32(), 1.0f});
				}
				if(chunks.Size() == 5)
				{
					pos.Add({chunks[1].Tof32(), chunks[2].Tof32(), chunks[3].Tof32(), chunks[4].Tof32()});	
				}
			}
			else if(line.BeginsWith('f'))
			{
				Array<String> chunks = line.Split(' ');
				for(u32 index = 1; index < chunks.Size(); index++)
				{
					Array<String> indices = chunks[index].Split('/');
					if(indices.Size() == 1)
					{
						u32 posIndex = (u32)(indices[0].Tos32() - 1);
						//vertices.add({pos[posIndex], {}, {}});
						vertices.Add(pos[posIndex]);
					}
					if(indices.Size() == 2)
					{
						u32 posIndex = (u32)(indices[0].Tos32() - 1);
						u32 texIndex = (u32)(indices[1].Tos32() - 1);
						//vertices.add({pos[posIndex], {}, texCoord[texIndex]});
						vertices.Add(pos[posIndex]);
					}
					if(indices.Size() == 3)
					{
						u32 posIndex = (u32)(indices[0].Tos32() - 1);
						
						u32 normIndex = (u32)(indices[2].Tos32() - 1);
						if(indices[1].Size() > 0)
						{
							u32 texIndex = (u32)(indices[1].Tos32() - 1);	
							//vertices.add({pos[posIndex], norm[normIndex], texCoord[texIndex]});
							vertices.Add(pos[posIndex]);
						}
						else
						{
							//vertices.add({pos[posIndex], norm[normIndex], {}});	
							vertices.Add(pos[posIndex]);	
						} 
						
					}
				}
			}
		}
		Mesh* result = new Mesh(vertices);
		return result;
	}
}