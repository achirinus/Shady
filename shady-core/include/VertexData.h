#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

namespace Shady
{
	namespace Graphics
	{
		struct VertexData
		{
			float * vertexCoords;
			int numOfvertices;
			int* indices;
			int numOfIndices;
			

			VertexData() {};
			VertexData(const VertexData& other)
			{
				vertexCoords = other.vertexCoords;
				indices = other.indices;
				numOfIndices = other.numOfIndices;
				numOfvertices = other.numOfvertices;

			}
			VertexData(const VertexData&& other)
			{
				vertexCoords = other.vertexCoords;
				indices = other.indices;
				numOfIndices = other.numOfIndices;
				numOfvertices = other.numOfvertices;
			}
		};
	}
}

#endif
