#ifndef __ResourceManager_H__
#define __ResourceManager_H__

class ResourceManager;

class ShaderProgram;
class Mesh;

class ResourceManager
{
protected:
    std::map<std::string, Mesh*> m_pMeshes;
    std::map<std::string, ShaderProgram*> m_pShaders;
    std::map<std::string, GLuint> m_pTextures;
    std::map<std::string, Material*> m_pMaterials;
	std::map<std::string, AudioCue*> m_pAudioCues;

public:
    ResourceManager();
    virtual ~ResourceManager();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);

    void AddMesh(const char* name, Mesh* pMesh) { m_pMeshes[name] = pMesh; }
    void AddShader(const char* name, ShaderProgram* pShader) { m_pShaders[name] = pShader; }
    void AddTexture(const char* name, GLuint texturehandle) { m_pTextures[name] = texturehandle; }
    void AddMaterial(const char* name, Material* pMaterial) { m_pMaterials[name] = pMaterial; }
	void AddAudioCue(const char* name, AudioCue* pAudioCue) { m_pAudioCues[name] = pAudioCue; }

    Mesh* GetMesh(const char* name) { return m_pMeshes[name]; }
    ShaderProgram* GetShader(const char* name) { return m_pShaders[name]; }
    GLuint GetTexture(const char* name) { return m_pTextures[name]; }
    Material* GetMaterial(const char* name) { return m_pMaterials[name]; }
	AudioCue* GetAudioCue(const char* name) { return m_pAudioCues[name]; }


    Mesh* GetMesh(std::string name) { return m_pMeshes[name]; }
    ShaderProgram* GetShader(std::string name) { return m_pShaders[name]; }
    GLuint GetTexture(std::string name) { return m_pTextures[name]; }
    Material* GetMaterial(std::string name) { return m_pMaterials[name]; }
	AudioCue* GetAudioCue(std::string name) { return m_pAudioCues[name]; }
};

#endif //__ResourceManager_H__
