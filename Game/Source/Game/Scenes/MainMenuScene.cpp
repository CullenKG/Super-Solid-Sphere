#include "GamePCH.h"



MainMenuScene::MainMenuScene(SceneManager* pSceneManager, ResourceManager* pResources) : Scene(pSceneManager, pResources)
{
    m_UpdateNextScene = true;
    m_IsOpaque = true;
	m_Tween = nullptr;
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
	Scene::OnSurfaceChanged(width, height);
}

void MainMenuScene::LoadContent()
{

    if (LoadSavedData("Data/SavedData/data.json") == false)
    {
        SetCompletedLevel("LevelOne", false);
        SetCompletedLevel("LevelTwo", false);
        SetOption("SoundOn", true);
        SetOption("Texture", true);
    }

	// Create some game objects.
	{
		// Camera
		m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -15), vec3(0, 0, 0), vec3(1, 1, 1));

		// Lights
		m_pLights["PointLight1"] = new PointLight(this, "PointLight1", vec3(0, 0, -5), 1.0f, 0.09f, 0.032f);
		m_pLights["PointLight1"]->SetLightColor(vec3(0.2f, 0.2f, 0.2f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f));

		m_pGameObjects["OptionsMenu"] = new GameObject(this, "OptionsMenu", vec3(0, 0, -2), vec3(0, 0, 0), vec3(0, 0, 0), "Box", "OptionsScene");

		// Background
		m_pGameObjects["Background"] = new GameObject(this, "Background", vec3(0, 0, 1), vec3(0, 0, 0), vec3(9, 9, 1), "Box", "MenuBackground");

		// Buttons
		m_pGameObjects["PlayButton"] = new MenuButtonObject(this, "PlayButton", vec3(0.2f, 1.7f, 0), vec3(0, 0, 0), vec3(2.6f, 0.8f, 0.8f), "Box", "PlayButton");
		m_pGameObjects["OptionsButton"] = new MenuButtonObject(this, "OptionsButton", vec3(0.2f, 0.5f, 0), vec3(0, 0, 0), vec3(2.6f, 0.8f, 0.8f), "Box", "OptionButton");
		m_pGameObjects["ExitButton"] = new MenuButtonObject(this, "ExitButton", vec3(0.2f, -0.7f, 0), vec3(0, 0, 0), vec3(2.6f, 0.8f, 0.8f), "Box", "QuitButton");
	}
}

void MainMenuScene::Update(float deltatime)
{
    m_MouseDepth = 0;

	Scene::Update(deltatime);

	if (m_Tween != nullptr)
	{
		if (m_Tween->IsFinished())
		{
			m_pGameObjects["OptionsMenu"]->SetScale(vec3(10, 10, 1));
			m_Tween = nullptr;
		}
		else
		{
			m_pGameObjects["OptionsMenu"]->SetScale(vec3(10, 10, 1) * m_Tween->GetCurrentPosition());
		}
	}

	if (m_pSceneManager->IsFrontScene(this))
	{
		m_pGameObjects["OptionsMenu"]->SetScale(vec3(0, 0, 0));

		if (m_pSceneManager->GetGame()->GetController(0)->IsButtonPressed(PCB_LeftMouse))
		{
			if (((MenuButtonObject*)m_pGameObjects["PlayButton"])->IsMouseOver(m_MouseWorldLocation))
			{
				m_pSceneManager->GetGame()->QueueEvent(new PushSceneEvent("LevelSelect"));
			}
			else if (((MenuButtonObject*)m_pGameObjects["OptionsButton"])->IsMouseOver(m_MouseWorldLocation))
			{
				m_pSceneManager->GetGame()->QueueEvent(new PushSceneEvent("Options"));

				m_Tween = m_pSceneManager->GetGame()->GetTweenManager()->StartTween(&TweenFunc_ElasticEaseOut, 0.0f, 1.0f, 0.7);
			}
			else if (((MenuButtonObject*)m_pGameObjects["ExitButton"])->IsMouseOver(m_MouseWorldLocation))
			{
                SaveData("Data/SavedData/data.json");
				exit(0);
			}
		}
	}
}

void MainMenuScene::Draw()
{
	Scene::Draw();
}