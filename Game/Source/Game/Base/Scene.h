#ifndef __Scene_H__
#define __Scene_H__

class SceneManager;
class GameObject;

class Scene
{
protected:
    SceneManager* m_pSceneManager;
    ResourceManager* m_pResources;

	FBODefinition* m_FBO;

    std::map<std::string, GameObject*> m_pGameObjects;
	std::map<std::string, LightObject*> m_pLights;

	static std::map<std::string, bool> m_CompletedLevels;
    static std::map<std::string, bool> m_Options;

    static bool m_HasSaved;

    BulletWorld* m_pBulletWorld;

	vec2 m_MouseWorldLocation;
    float m_MouseDepth;

    bool m_UpdateNextScene;
    bool m_IsOpaque;

public:
    Scene(SceneManager* pSceneManager, ResourceManager* pResources);
    virtual ~Scene();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltatime);
    virtual void Draw();
	virtual void RenderSceneToTexture();

    static void SetOption(std::string option, bool isOn);
    static void SetCompletedLevel(std::string option, bool isFinished);

    static bool GetOption(std::string option);
    static bool GetCompletedLevel(std::string option);


	bool LoadSavedData(const char* filename);
    void SaveData(const char* filename);

    SceneManager* GetSceneManager() { return m_pSceneManager; }
    ResourceManager* GetResourceManager() { return m_pResources; }

    GameObject* GetGameObject(const char* name) { return m_pGameObjects[name]; }
	GameObject* GetLight(const char* name) { return m_pLights[name]; }
	auto GetAllLightsInScene() { return m_pLights; }

    BulletWorld* GetBulletWorld() { return m_pBulletWorld; }

	vec2 GetMouseWorldLocation() { return m_MouseWorldLocation; }

    void SetMouseDepth(float depth) { m_MouseDepth = depth; }

    bool SendsUpdateToNextScene() { return m_UpdateNextScene; }
    bool IsOpaque() { return m_IsOpaque; }
};

#endif //__Scene_H__
