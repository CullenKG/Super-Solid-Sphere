#ifndef __Mesh_H__
#define __Mesh_H__

class LightObject;

class Mesh
{
protected:
    GLuint m_VBO;
    GLuint m_IBO;

    unsigned int m_NumVerts;
    unsigned int m_NumIndices;

    GLenum m_PrimitiveType;

    static int FindSimilarVertexIndex(vec3 position, vec2 uv, vec3 normal, std::vector<vec3> &verticies, std::vector<vec2> &uvs, std::vector<vec3> &normals, int index);

public:
    Mesh();
    virtual ~Mesh();

    virtual void Init(VertexFormat* verts, int numverts, unsigned int* indices, int numindices, GLenum usage);
    virtual void Init(const void* verts, int numverts, int vertexbytesize, GLenum usage);

    virtual void SetupAttributes(ShaderProgram* pShaderProgram);
	virtual void SetupUniforms(Material* pMaterial, mat4* pMatWorld, mat4* pMatView, mat4* pMatProj, vec3 campos, const std::map<std::string, LightObject*> &lightObjects);
	virtual void SetupUniform1f(ShaderProgram* pShader, std::string uniform, float value);
    virtual void Draw(ShaderProgram* pShaderProgram);

    // The following functions are defined in MeshShapes.cpp
    static Mesh* CreateBox(vec2 size);
    static Mesh* CreateCube(vec3 size);
    static Mesh* CreatePlane(Vector3 topleftpos, Vector2 size, Vector2Int vertcount, Vector2 uvstart, Vector2 uvrange);
    static Mesh* LoadObject(const char* filename);
};

#endif //__Game_H__
