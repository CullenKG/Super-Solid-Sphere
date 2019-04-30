#include "GamePCH.h"

std::map<std::string, bool> Scene::m_CompletedLevels;
std::map<std::string, bool> Scene::m_Options;
bool Scene::m_HasSaved;

Scene::Scene(SceneManager* pSceneManager, ResourceManager* pResources)
{
    m_pSceneManager = pSceneManager;
    m_pResources = pResources;

    m_pBulletWorld = 0;
    m_MouseDepth = 0;
    m_FBO = 0;

    m_HasSaved = false;
}

Scene::~Scene()
{
    for (auto object : m_pGameObjects)
    {
        delete object.second;
    }

    for (auto light : m_pLights)
    {
        delete light.second;
    }

    delete m_FBO;
    delete m_pBulletWorld;

    m_CompletedLevels.clear();
    m_Options.clear();
}

void Scene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
}

void Scene::LoadContent()
{
    m_FBO = new FBODefinition();
    m_FBO->Create(1024, 1024, GL_NEAREST, GL_NEAREST, true, 24, true);
}

void Scene::OnEvent(Event* pEvent)
{
    if (pEvent->GetEventType() == EventType_Reset)
    {
        for (auto object : m_pGameObjects)
            object.second->Reset();
    }
}

void Scene::Update(float deltatime)
{
    CheckForGLErrors();

    // Calculate mouse position in world space
    {
        // Get mouse location in windows screen space
        vec2 m_MouseLocation = m_pSceneManager->GetGame()->GetController(0)->GetMouseLocation();

        // Get screen size
        ivec2 screenSize = ivec2(m_pSceneManager->GetGame()->GetWindowWidth(), m_pSceneManager->GetGame()->GetWindowHeight());

        // Get projection and view matricies
        mat4 ProjMatrix = *((CameraObject*)m_pGameObjects["Camera"])->GetProjMatrix();
        mat4 ViewMatrix = *((CameraObject*)m_pGameObjects["Camera"])->GetViewMatrix();

        // Calculate the inverse projection view matrix
        mat4 inverseProjectionView = ProjMatrix * ViewMatrix;
        inverseProjectionView.Inverse();

        // Calculate mouse position in NDC space
        vec2 mouseNDC = vec2(2.0f * m_MouseLocation.x / screenSize.x - 1, -2.0f * m_MouseLocation.y / screenSize.y + 1);

        // Get mouse z position
        vec4 objectView = ViewMatrix * vec4(0, 0, m_MouseDepth, 1);
        vec4 objectClip = ProjMatrix * objectView;

        // This works some how
        float z = objectClip.z / objectView.z;

        // Multiply the mouseposition by the inverse projectionview matrix
        vec4 finalMousePos = inverseProjectionView * vec4(mouseNDC, z, 1);

        // Divide position by w
        finalMousePos.x /= finalMousePos.w;
        finalMousePos.y /= finalMousePos.w;

        // Mouse in world location
        m_MouseWorldLocation = vec2(finalMousePos.x, finalMousePos.y);
    }

    if (m_pBulletWorld)
    {
        m_pBulletWorld->Update(deltatime);
    }

    // Update all of the Scene objects in the list.
    for (auto object : m_pGameObjects)
    {
        object.second->Update(deltatime);
    }

    CheckForGLErrors();
}

void Scene::Draw()
{
    CheckForGLErrors();

    CameraObject* pCamera = (CameraObject*)GetGameObject("Camera");

    if (pCamera)
    {
        vec3 campos = pCamera->GetPosition();
        mat4* pMatView = pCamera->GetViewMatrix();
        mat4* pMatViewSkybox = pCamera->GetViewSkyBoxMatrix();
        mat4* pMatProj = pCamera->GetProjMatrix();

        // Render all of the Scene objects in the list.
        for (int i = 0; i < 5; i++)
        {
            for (auto object : m_pGameObjects)
            {
                if (object.second->GetRenderOrder() == i)
                {
                    if (object.first == "Skybox")
                    {
                        object.second->Draw(i, pMatViewSkybox, pMatProj, campos);
                    }
                    else
                    {
                        object.second->Draw(i, pMatView, pMatProj, campos);
                    }
                }
            }
        }
    }

    CheckForGLErrors();
}

bool Scene::LoadSavedData(const char* filename)
{
    char* contents = LoadCompleteFile(filename, 0);

    if (contents == 0)
        return false;

    cJSON* root = cJSON_Parse(contents);

    delete[] contents;

    cJSON* optionsArray = cJSON_GetObjectItemCaseSensitive(root, "Options");
    int numOptions = cJSON_GetArraySize(optionsArray);

    if (numOptions == 0)
        return false;


    cJSON* jSoundOnOption = cJSON_GetArrayItem(optionsArray, 0);
    cJSON* jSoundOption = cJSON_GetObjectItemCaseSensitive(jSoundOnOption, "SoundOn");
    bool soundOn = jSoundOption->valueint;
    m_Options["SoundOn"] = soundOn;

    cJSON* jTextureChangeOption = cJSON_GetArrayItem(optionsArray, 1);
    cJSON* jTextureOption = cJSON_GetObjectItemCaseSensitive(jTextureChangeOption, "Texture");
    bool textureChange = jTextureOption->valueint;
    m_Options["Texture"] = textureChange;


    cJSON* levelsArray = cJSON_GetObjectItemCaseSensitive(root, "CompletedLevels");
    int numLevels = cJSON_GetArraySize(levelsArray);

    if (numLevels == 0)
        return false;

    cJSON* jLevel1Item = cJSON_GetArrayItem(levelsArray, 0);
    cJSON* jLevel1 = cJSON_GetObjectItemCaseSensitive(jLevel1Item, "LevelOne");
    bool level1Complete = jLevel1->valueint;
    m_CompletedLevels["LevelOne"] = level1Complete;

    cJSON* jLevel2Item = cJSON_GetArrayItem(levelsArray, 1);
    cJSON* jLevel2 = cJSON_GetObjectItemCaseSensitive(jLevel2Item, "LevelTwo");
    bool level2Complete = jLevel2->valueint;
    m_CompletedLevels["LevelTwo"] = level2Complete;

    cJSON_Delete(root);

    return true;
}

void Scene::SaveData(const char* filename)
{
    if (m_HasSaved == false)
    {
        cJSON* jRoot = cJSON_CreateObject();

        cJSON* jOptionsArray = cJSON_CreateArray();
        cJSON_AddItemToObject(jRoot, "Options", jOptionsArray);

        cJSON* jCompletedLevelsArray = cJSON_CreateArray();
        cJSON_AddItemToObject(jRoot, "CompletedLevels", jCompletedLevelsArray);

        for (auto option : m_Options)
        {
            cJSON* jLevel = cJSON_CreateObject();
            cJSON_AddBoolToObject(jLevel, option.first.c_str(), option.second);

            cJSON_AddItemToObject(jOptionsArray, option.first.c_str(), jLevel);
        }

        for (auto level : m_CompletedLevels)
        {
            cJSON* jLevel = cJSON_CreateObject();
            cJSON_AddBoolToObject(jLevel, level.first.c_str(), level.second);

            cJSON_AddItemToObject(jCompletedLevelsArray, level.first.c_str(), jLevel);
        }

        char* jsonChar = cJSON_Print(jRoot);

        std::string jsonString = jsonChar;

        FILE* filehandle;
        errno_t error = fopen_s(&filehandle, filename, "wb");
        if (filehandle)
        {
            fwrite(jsonChar, 1, jsonString.length(), filehandle);
            fclose(filehandle);
        }
        free(jsonChar);

        m_HasSaved = true;
    }
}

void Scene::RenderSceneToTexture()
{
    CheckForGLErrors();

    CameraObject* pCamera = (CameraObject*)GetGameObject("Camera");

    if (pCamera)
    {
        vec3 campos = pCamera->GetPosition();
        mat4* pMatView = pCamera->GetViewMatrix();
        mat4* pMatViewSkybox = pCamera->GetViewSkyBoxMatrix();
        mat4* pMatProj = pCamera->GetProjMatrix();

        m_FBO->Bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, 1024, 1024);

        // Render all of the Scene objects in the list.
        for (int i = 0; i < 5; i++)
        {
            for (auto object : m_pGameObjects)
            {
                if (object.second->GetRenderOrder() == i)
                {
                    if (object.first == "Skybox")
                    {
                        object.second->Draw(i, pMatViewSkybox, pMatProj, campos);
                    }
                    else
                    {
                        object.second->Draw(i, pMatView, pMatProj, campos);
                    }
                }
            }
        }

        m_FBO->Unbind();
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, 1024, 1024);
    }
}

void Scene::SetOption(std::string option, bool isOn)
{
    m_Options[option] = isOn;
}

void Scene::SetCompletedLevel(std::string option, bool isFinished)
{
    m_CompletedLevels[option] = isFinished;
}

bool Scene::GetOption(std::string option)
{
    return m_Options[option];
}

bool Scene::GetCompletedLevel(std::string option)
{
    return m_CompletedLevels[option];
}
