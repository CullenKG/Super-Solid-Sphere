#include "GamePCH.h"

OptionsScene::OptionsScene(SceneManager* pSceneManager, ResourceManager* pResources) : Scene(pSceneManager, pResources)
{
    m_IsOpaque = false;
    m_UpdateNextScene = true;
}

OptionsScene::~OptionsScene()
{
}

void OptionsScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged(width, height);
}

void OptionsScene::LoadContent()
{
	Scene::LoadContent();

	m_pResources->AddMaterial("OptionsScene", new Material(m_pResources->GetShader("Texture"), m_FBO->GetColorTextureHandle()));

    // Create some game objects.
    {
        // Camera
        m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -15), vec3(0, 0, 0), vec3(1, 1, 1));

        // Buttons
        m_pGameObjects["Background"] = new GameObject(this, "Background", vec3(0, 0, -1), vec3(0, 0, 0), vec3(5, 5, 5), "Box", "OptionsMenuBackground");

        m_pGameObjects["BackButton"] = new MenuButtonObject(this, "BackButton", vec3(-1.6f, -1.5f, -2), vec3(0, 0, 0), vec3(0.7f, 0.7f, 1), "Box", "BackButton");
        m_pGameObjects["BackButton"]->SetRenderOrder(2);

        m_pGameObjects["OptionBlue"] = new MenuButtonObject(this, "OptionBlue", vec3(-1.6f, 0.4f, -2), vec3(0, 0, 0), vec3(0.7f, 0.7f, 1), "Box", "BlueButton");
        m_pGameObjects["OptionBlue"]->SetRenderOrder(2);

        m_pGameObjects["OptionSalad"] = new MenuButtonObject(this, "OptionSalad", vec3(-0.8f, 0.4f, -2), vec3(0, 0, 0), vec3(0.7f, 0.7f, 1), "Box", "SaladButton");
        m_pGameObjects["OptionSalad"]->SetRenderOrder(2);

        m_pGameObjects["OptionVolumeOff"] = new MenuButtonObject(this, "OptionVolumeOff", vec3(-1.8f, 1.8f, -2), vec3(0, 0, 0), vec3(0.7f, 0.7f, 1), "Box", "VolumeOffButton");
        m_pGameObjects["OptionVolumeOff"]->SetRenderOrder(2);

        m_pGameObjects["OptionVolumeOn"] = new MenuButtonObject(this, "OptionVolumeOn", vec3(1.8f, 1.8f, -2), vec3(0, 0, 0), vec3(0.7f, 0.7f, 1), "Box", "VolumeOnButton");
        m_pGameObjects["OptionVolumeOn"]->SetRenderOrder(2);
    }
}

void OptionsScene::Update(float deltatime)
{
    m_MouseDepth = -2;

    Scene::Update(deltatime);

    if (m_pSceneManager->GetGame()->GetController(0)->IsButtonPressed(PCB_LeftMouse))
    {
        if (((MenuButtonObject*)m_pGameObjects["BackButton"])->IsMouseOver(m_MouseWorldLocation))
        {
            m_pSceneManager->GetGame()->QueueEvent(new PopSceneEvent(false));
        }
        if (((MenuButtonObject*)m_pGameObjects["OptionVolumeOn"])->IsMouseOver(m_MouseWorldLocation))
        {
            SetOption("VolumeOn", true);
        }
        if (((MenuButtonObject*)m_pGameObjects["OptionVolumeOff"])->IsMouseOver(m_MouseWorldLocation))
        {
            SetOption("VolumeOn", false);
        }
        if (((MenuButtonObject*)m_pGameObjects["OptionVolumeOn"])->IsMouseOver(m_MouseWorldLocation))
        {
            SetOption("Texture", true);
        }
        if (((MenuButtonObject*)m_pGameObjects["OptionSalad"])->IsMouseOver(m_MouseWorldLocation))
        {
            SetOption("Texture", false);
        }
    }
}

void OptionsScene::Draw()
{
	RenderSceneToTexture();
}