#include "GamePCH.h"

Mesh* Mesh::CreateBox(vec2 size)
{
	VertexFormat verts[4];

	verts[0] = VertexFormat(-size.x / 2, -size.y / 2, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0);
	verts[1] = VertexFormat(-size.x / 2, size.y / 2, 0, 255, 255, 255, 255, 0, 1, 0, 0, 0);
	verts[2] = VertexFormat(size.x / 2, size.y / 2, 0, 255, 255, 255, 255, 1, 1, 0, 0, 0);
	verts[3] = VertexFormat(size.x / 2, -size.y / 2, 0, 255, 255, 255, 255, 1, 0, 0, 0, 0);

	unsigned int indices[6] = { 0,1,2, 0,2,3 };

	Mesh* pMesh = new Mesh();
	pMesh->Init(verts, 4, indices, 6, GL_STATIC_DRAW);

	return pMesh;
};

Mesh* Mesh::CreateCube(vec3 size)
{
	VertexFormat verts[24];

	verts[0] = VertexFormat(-size.x / 2, -size.y / 2, -size.z / 2, 255, 0, 0, 255, 0, 1 / 3.0f, 0, 0, 0); // F BL R
	verts[1] = VertexFormat(-size.x / 2, size.y / 2, -size.z / 2, 255, 0, 0, 255, 0, 2 / 3.0f, 0, 0, 0); // F TL R
	verts[2] = VertexFormat(size.x / 2, size.y / 2, -size.z / 2, 255, 0, 0, 255, 0.25, 2 / 3.0f, 0, 0, 0); // F TR R
	verts[3] = VertexFormat(size.x / 2, -size.y / 2, -size.z / 2, 255, 0, 0, 255, 0.25, 1 / 3.0f, 0, 0, 0); // F BR R

	verts[4] = VertexFormat(-size.x / 2, -size.y / 2, size.z / 2, 255, 0, 0, 255, 0.75, 1 / 3.0f, 0, 0, 0); // B BL R
	verts[5] = VertexFormat(-size.x / 2, size.y / 2, size.z / 2, 255, 0, 0, 255, 0.75, 2 / 3.0f, 0, 0, 0); // B TL R
	verts[6] = VertexFormat(size.x / 2, size.y / 2, size.z / 2, 255, 0, 0, 255, 0.5, 2 / 3.0f, 0, 0, 0); // B TR R
	verts[7] = VertexFormat(size.x / 2, -size.y / 2, size.z / 2, 255, 0, 0, 255, 0.5, 1 / 3.0f, 0, 0, 0); // B BR R

	verts[8] = VertexFormat(-size.x / 2, -size.y / 2, -size.z / 2, 0, 255, 0, 255, 0.5, 1 / 3.0f, 0, 0, 0); // F BL G
	verts[9] = VertexFormat(-size.x / 2, size.y / 2, -size.z / 2, 0, 255, 0, 255, 0.5, 2 / 3.0f, 0, 0, 0); // F TL G
	verts[10] = VertexFormat(size.x / 2, size.y / 2, -size.z / 2, 0, 255, 0, 255, 0.75, 2 / 3.0f, 0, 0, 0); // F TR G
	verts[11] = VertexFormat(size.x / 2, -size.y / 2, -size.z / 2, 0, 255, 0, 255, 0.75, 1 / 3.0f, 0, 0, 0); // F BR G

	verts[12] = VertexFormat(-size.x / 2, -size.y / 2, size.z / 2, 0, 255, 0, 255, 0.5, 0, 0, 0, 0); // B BL G
	verts[13] = VertexFormat(-size.x / 2, size.y / 2, size.z / 2, 0, 255, 0, 255, 0.5, 1, 0, 0, 0); // B TL G
	verts[14] = VertexFormat(size.x / 2, size.y / 2, size.z / 2, 0, 255, 0, 255, 0.75, 1, 0, 0, 0); // B TR G
	verts[15] = VertexFormat(size.x / 2, -size.y / 2, size.z / 2, 0, 255, 0, 255, 0.75, 0, 0, 0, 0); // B BR G

	verts[16] = VertexFormat(-size.x / 2, -size.y / 2, -size.z / 2, 0, 0, 255, 255, 1, 1 / 3.0f, 0, 0, 0); // F BL B
	verts[17] = VertexFormat(-size.x / 2, size.y / 2, -size.z / 2, 0, 0, 255, 255, 1, 2 / 3.0f, 0, 0, 0); // F TL B


	verts[18] = VertexFormat(size.x / 2, size.y / 2, -size.z / 2, 0, 0, 255, 255, 1, 1, 0, 0, 0); // F TR B
	verts[19] = VertexFormat(size.x / 2, -size.y / 2, -size.z / 2, 0, 0, 255, 255, 1, 0, 0, 0, 0); // F BR B

	verts[20] = VertexFormat(-size.x / 2, -size.y / 2, size.z / 2, 0, 0, 255, 255, 0, 0, 0, 0, 0); // B BL B
	verts[21] = VertexFormat(-size.x / 2, size.y / 2, size.z / 2, 0, 0, 255, 255, 0, 1, 0, 0, 0); // B TL B
	verts[22] = VertexFormat(size.x / 2, size.y / 2, size.z / 2, 0, 0, 255, 255, 1, 1, 0, 0, 0); // B TR B
	verts[23] = VertexFormat(size.x / 2, -size.y / 2, size.z / 2, 0, 0, 255, 255, 1, 0, 0, 0, 0); // B BR B

	//TEXTURE
	unsigned int indices[36] = { 0, 1, 2,  0, 2, 3,  2, 3, 6,  3, 7, 6,  6, 4, 5,  6, 4, 7,  5, 16, 4,  16, 17, 5,  8, 12, 15,  8, 11, 15,  9, 13, 14,  9, 10, 14 };

	Mesh* pMesh = new Mesh();
	pMesh->Init(verts, 18, indices, 36, GL_STATIC_DRAW);

	return pMesh;
};

Mesh* Mesh::CreatePlane(Vector3 topleftpos, Vector2 size, Vector2Int vertcount, Vector2 uvstart, Vector2 uvrange)
{
	int numverts = vertcount.x * vertcount.y;
	int numindices = (vertcount.x - 1) * (vertcount.y - 1) * 6;

	VertexFormat* verts = new VertexFormat[numverts];
	unsigned int* indices = new unsigned int[numindices];

	float stepx = size.x / (vertcount.x - 1);
	float stepz = size.y / (vertcount.y - 1);
	float stepu = uvrange.x / (vertcount.x - 1);
	float stepv = uvrange.y / (vertcount.y - 1);

	for (int z = 0; z < vertcount.y; z++)
	{
		for (int x = 0; x < vertcount.x; x++)
		{
			float posx = topleftpos.x + x * stepx;
			float posz = topleftpos.z + z * stepz;
			float uvx = uvstart.x + x * stepu;
			float uvz = uvstart.y + z * stepv;

			verts[z * vertcount.x + x] = VertexFormat(posx, topleftpos.y, posz, 255, 255, 255, 255, uvx, uvz, 0, 0, 0);
		}
	}

	for (int y = 0; y < vertcount.y - 1; y++)
	{
		for (int x = 0; x < vertcount.x - 1; x++)
		{
			indices[(y * (vertcount.x - 1) + x) * 6 + 0] = (y * vertcount.x + x) + 0;
			indices[(y * (vertcount.x - 1) + x) * 6 + 1] = (y * vertcount.x + x) + 1;
			indices[(y * (vertcount.x - 1) + x) * 6 + 2] = (y * vertcount.x + x) + vertcount.x;

			indices[(y * (vertcount.x - 1) + x) * 6 + 3] = (y * vertcount.x + x) + 1;
			indices[(y * (vertcount.x - 1) + x) * 6 + 4] = (y * vertcount.x + x) + vertcount.x + 1;
			indices[(y * (vertcount.x - 1) + x) * 6 + 5] = (y * vertcount.x + x) + vertcount.x;
		}
	}

	Mesh* pMesh = new Mesh();
	pMesh->Init(verts, numverts, indices, numindices, GL_STATIC_DRAW);
	pMesh->m_PrimitiveType = GL_TRIANGLES;

	delete[] verts;
	delete[] indices;

	return pMesh;
};

Mesh* Mesh::LoadObject(const char* filename)
{
	long length = 0;
	char* buffer = LoadCompleteFile(filename, &length);

	if (buffer == 0 || length == 0)
	{
		delete buffer;
		return 0;
	}

	std::vector<Vector3> VertexPositions;
	std::vector<Vector2> UVCoordinates;
	std::vector<Vector3> VertexNormals;
	std::vector<Vector3> Tangents;

	std::vector<int> VertexPositionIndicies;
	std::vector<int> UVCoordinateIndicies;
	std::vector<int> VertexNormalIndicies;
	std::vector<int> TangentIndicies;

	std::vector<VertexFormat> Verticies;

	std::vector<Vector3> TempVertexPositions;
	std::vector<Vector2> TempUVCoordinates;
	std::vector<Vector3> TempVertexNormals;

	char* next_token = 0;
	char* line = strtok_s(buffer, "\n", &next_token);

	while (line)
	{
		char type[128];

		sscanf_s(line, "%s", type, 128);

		if (strcmp(type, "v") == 0)
		{
			vec3 vertexPos;

			sscanf_s(line, "%*s %f %f %f", &vertexPos.x, &vertexPos.y, &vertexPos.z);

			TempVertexPositions.push_back(vertexPos);
		}
		else if (strcmp(type, "vt") == 0)
		{
			vec2 uv;

			sscanf_s(line, "%*s %f %f", &uv.x, &uv.y);

			TempUVCoordinates.push_back(uv);
		}
		else if (strcmp(type, "vn") == 0)
		{
			vec3 normal;

			sscanf_s(line, "%*s %f %f %f", &normal.x, &normal.y, &normal.z);

			TempVertexNormals.push_back(normal);
		}
		else if (strcmp(type, "f") == 0)
		{
			unsigned int vertexPositionIndicies[3];
			unsigned int uvCoordinateIndicies[3];
			unsigned int vertexNormalIndicies[3];

			sscanf_s(line, "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &vertexPositionIndicies[0], &uvCoordinateIndicies[0], &vertexNormalIndicies[0], &vertexPositionIndicies[1], &uvCoordinateIndicies[1], &vertexNormalIndicies[1], &vertexPositionIndicies[2], &uvCoordinateIndicies[2], &vertexNormalIndicies[2]);			

			for (int i = 0; i < 3; i++)
			{
				VertexPositionIndicies.push_back(vertexPositionIndicies[i]);
				UVCoordinateIndicies.push_back(uvCoordinateIndicies[i]);
				VertexNormalIndicies.push_back(vertexNormalIndicies[i]);
			}
		}

		line = strtok_s(0, "\n", &next_token);
	}
	
	for (unsigned int i = 0; i < VertexPositionIndicies.size(); i++)
	{
		unsigned int vertexIndex = VertexPositionIndicies[i];
		unsigned int uvIndex = UVCoordinateIndicies[i];
		unsigned int normalIndex = VertexNormalIndicies[i];

		vec3 pos = TempVertexPositions[vertexIndex - 1];
		vec2 uv = TempUVCoordinates[uvIndex - 1];
		vec3 normal = TempVertexNormals[normalIndex - 1];

		VertexPositions.push_back(pos);
		UVCoordinates.push_back(uv);
		VertexNormals.push_back(normal);
	}


	for (unsigned int i = 0; i < VertexPositions.size(); i += 3)
	{
		vec3 pos0 = VertexPositions[i];
		vec3 pos1 = VertexPositions[i + 1];
		vec3 pos2 = VertexPositions[i + 2];

		vec2 uv0 = UVCoordinates[i];
		vec2 uv1 = UVCoordinates[i + 1];
		vec2 uv2 = UVCoordinates[i + 2];

		vec3 deltaPos1 = pos1 - pos0;
		vec3 deltaPos2 = pos2 - pos0;

		vec2 deltaUV1 = uv1 - uv0;
		vec2 deltaUV2 = uv2 - uv0;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        vec3 tangent;
        tangent.x = f * (deltaUV2.y * deltaPos1.x - deltaUV1.y * deltaPos2.x);
        tangent.y = f * (deltaUV2.y * deltaPos1.y - deltaUV1.y * deltaPos2.y);
        tangent.z = f * (deltaUV2.y * deltaPos1.z - deltaUV1.y * deltaPos2.z);
		tangent.Normalize();

		for (int j = 0; j < 3; j++)
		{
			Tangents.push_back(tangent);
		}
	}

	for (unsigned int i = 0; i < VertexPositions.size(); i += 3)
	{
		for (int j = 0; j < 3; j++)
		{
			int index = i + j;

			Vector3 position = VertexPositions[index];
			Vector2 uv = UVCoordinates[index];
			Vector3 normal = VertexNormals[index];

			int foundIndex = FindSimilarVertexIndex(position, uv, normal, VertexPositions, UVCoordinates, VertexNormals, index);

			if (foundIndex != -1)
			{
				TangentIndicies.push_back(foundIndex);

				Tangents[foundIndex] += Tangents[index];
			}
			else
			{
				TangentIndicies.push_back(index);
			}
		}
	}

	for (unsigned int i = 0; i < VertexPositions.size(); i += 3)
	{
		for (int j = 0; j < 3; j++)
		{
			int index = i + j;

			Vector3 position = VertexPositions[index];
			Vector2 uv = UVCoordinates[index];
			Vector3 normal = VertexNormals[index];
			Vector3 tangent = Tangents[TangentIndicies[index]];

			Verticies.push_back(VertexFormat(position, MyColor(255, 255, 255, 255), uv, normal, tangent));
		}
	}

	delete[] buffer;

	Mesh* pMesh = new Mesh();
	pMesh->Init(Verticies.data(), Verticies.size(), 0, 0, GL_STATIC_DRAW);
	pMesh->m_PrimitiveType = GL_TRIANGLES;

	return pMesh;
};
