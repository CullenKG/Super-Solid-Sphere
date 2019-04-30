#include "GamePCH.h"

LoadingScene::LoadingScene(SceneManager* pSceneManager, ResourceManager* pResources) : Scene(pSceneManager, pResources),
m_CurrentLoadingStep(LoadingStep_Shaders)
{
    m_IsOpaque = true;
    m_UpdateNextScene = false;
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
	Scene::OnSurfaceChanged(width, height);
}

void LoadingScene::LoadContent()
{
	// Create some game objects.
	{
		// Load resources needed for loading screen
		{
			m_pResources->AddMesh("Box", Mesh::CreateBox(vec2(1, 1)));

			m_pResources->AddShader("Texture", new ShaderProgram("Data/Shaders/texture.vert", "Data/Shaders/texture.frag"));
			m_pResources->AddShader("ProgressBar", new ShaderProgram("Data/Shaders/ProgressBar.vert", "Data/Shaders/ProgressBar.frag"));

			m_pResources->AddTexture("LoadingBar_Background", LoadTexture("Data/Textures/LoadingBar/LoadingBar_Background.png"));
			m_pResources->AddTexture("LoadingBar_Bar", LoadTexture("Data/Textures/LoadingBar/LoadingBar_Bar.png"));

			m_pResources->AddMaterial("LoadingBar_Background", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("LoadingBar_Background")));
			m_pResources->AddMaterial("LoadingBar_Bar", new Material(m_pResources->GetShader("ProgressBar"), m_pResources->GetTexture("LoadingBar_Bar")));
		}

		// Create objects needed for loading screen
		{
			// Camera
			m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, 0, -20), vec3(0, 0, 0), vec3(1, 1, 1));

			m_pGameObjects["LoadingBar_Background"] = new GameObject(this, "LoadingBar_Background", vec3(0, 0, 0), vec3(0, 0, 0), vec3(10.0f, 2, 1), "Box", "LoadingBar_Background");
			m_pGameObjects["LoadingBar_Bar"] = new GameObject(this, "LoadingBar_Background", vec3(0, 0, 0), vec3(0, 0, 0), vec3(10.0f, 2, 1), "Box", "LoadingBar_Bar");
			m_pGameObjects["LoadingBar_Bar"]->SetRenderOrder(1);
		}		
	}
}

void LoadingScene::Update(float deltatime)
{
	Scene::Update(deltatime);

	Load(m_CurrentLoadingStep);
}

void LoadingScene::Draw()
{
	Scene::Draw();
}

void LoadingScene::Load(LoadingStep step)
{
	if (step == LoadingStep_Shaders)
	{
		// Load shaders
		m_pResources->AddShader("Cubemap", new ShaderProgram("Data/Shaders/Cubemap.vert", "Data/Shaders/Cubemap.frag"));
		m_pResources->AddShader("LitTexture", new ShaderProgram("Data/Shaders/LitTexture.vert", "Data/Shaders/LitTexture.frag"));
		m_pResources->AddShader("LitReflectiveTexture", new ShaderProgram("Data/Shaders/LitReflectiveTexture.vert", "Data/Shaders/LitReflectiveTexture.frag"));
		m_pResources->AddShader("LitColor", new ShaderProgram("Data/Shaders/LitColor.vert", "Data/Shaders/LitColor.frag"));
	}
	else if (step == LoadingStep_Audio)
	{
		// Load audio
		SoundPlayer* soundPlayer = new SoundPlayer();

		// Pickup sounds
		AudioCue* pPickupCue = new AudioCue();
		pPickupCue->AddSound(soundPlayer->LoadSound("Data/Audio/Pickup_Coin.wav"));
		pPickupCue->AddSound(soundPlayer->LoadSound("Data/Audio/Pickup_Coin2.wav"));
		pPickupCue->AddSound(soundPlayer->LoadSound("Data/Audio/Pickup_Coin3.wav"));
		pPickupCue->AddSound(soundPlayer->LoadSound("Data/Audio/Pickup_Coin4.wav"));
		pPickupCue->AddSound(soundPlayer->LoadSound("Data/Audio/Pickup_Coin5.wav"));

		m_pResources->AddAudioCue("Pickup", pPickupCue);

		// Menu select sounds
		pPickupCue = new AudioCue();
		pPickupCue->AddSound(soundPlayer->LoadSound("Data/Audio/Menu_Select.wav"));
		pPickupCue->AddSound(soundPlayer->LoadSound("Data/Audio/Menu_Select2.wav"));
		pPickupCue->AddSound(soundPlayer->LoadSound("Data/Audio/Menu_Select3.wav"));

		m_pResources->AddAudioCue("MenuSelect", pPickupCue);

		delete soundPlayer;
	}
	else if (step == LoadingStep_Meshes)
	{
		// Load meshes
		m_pResources->AddMesh("Sphere", Mesh::LoadObject("Data/Objects/sphere.obj"));
		m_pResources->AddMesh("Cube", Mesh::LoadObject("Data/Objects/cube.obj"));
		m_pResources->AddMesh("Skybox", Mesh::LoadObject("Data/Objects/skybox.obj"));
	}
	else if (step == LoadingStep_TextureGroup1)
	{
		// Skybox
		const char** filenames = new const char*[6];
		filenames[0] = "Data/Textures/Skybox/right.png";
		filenames[1] = "Data/Textures/Skybox/left.png";
		filenames[2] = "Data/Textures/Skybox/top.png";
		filenames[3] = "Data/Textures/Skybox/bottom.png";
		filenames[4] = "Data/Textures/Skybox/front.png";
		filenames[5] = "Data/Textures/Skybox/back.png";

		m_pResources->AddTexture("Skybox_Cubemap", LoadTextureCubemap(filenames));

		delete[] filenames;

		// Cobblestone texture
		m_pResources->AddTexture("Cobblestone_Diffuse", LoadTexture("Data/Textures/Cobblestone/Cobblestone_Diffuse.png"));
		m_pResources->AddTexture("Cobblestone_Specular", LoadTexture("Data/Textures/Cobblestone/Cobblestone_Specular.png"));
		m_pResources->AddTexture("Cobblestone_Normal", LoadTexture("Data/Textures/Cobblestone/Cobblestone_Normal.png"));
	}
	else if (step == LoadingStep_TextureGroup2)
	{
		// Brick texture
		m_pResources->AddTexture("Brick_Diffuse", LoadTexture("Data/Textures/Brick/Brick_Diffuse.png"));
		m_pResources->AddTexture("Brick_Specular", LoadTexture("Data/Textures/Brick/Brick_Specular.png"));
		m_pResources->AddTexture("Brick_Normal", LoadTexture("Data/Textures/Brick/Brick_Normal.png"));

		// Snow texture
		m_pResources->AddTexture("Snow_Diffuse", LoadTexture("Data/Textures/Snow/Snow_Diffuse.png"));
		m_pResources->AddTexture("Snow_Specular", LoadTexture("Data/Textures/Snow/Snow_Specular.png"));
		m_pResources->AddTexture("Snow_Normal", LoadTexture("Data/Textures/Snow/Snow_Normal.png"));

	}
	else if (step == LoadingStep_TextureGroup3)
	{
		// Stone texture
		m_pResources->AddTexture("Stone_Diffuse", LoadTexture("Data/Textures/Stone/Stone_Diffuse.png"));
		m_pResources->AddTexture("Stone_Specular", LoadTexture("Data/Textures/Stone/Stone_Specular.png"));
		m_pResources->AddTexture("Stone_Normal", LoadTexture("Data/Textures/Stone/Stone_Normal.png"));

		// StoneWall
		m_pResources->AddTexture("StoneWall_Diffuse", LoadTexture("Data/Textures/StoneWall/StoneWall_Diffuse.png"));
		m_pResources->AddTexture("StoneWall_Specular", LoadTexture("Data/Textures/StoneWall/StoneWall_Specular.png"));
		m_pResources->AddTexture("StoneWall_Normal", LoadTexture("Data/Textures/StoneWall/StoneWall_Normal.png"));
	}
	else if (step == LoadingStep_TextureGroup4)
	{
		// Crystal texture
		m_pResources->AddTexture("Crystal_Diffuse", LoadTexture("Data/Textures/Crystal/Crystal_Diffuse.png"));
		m_pResources->AddTexture("Crystal_Specular", LoadTexture("Data/Textures/Crystal/Crystal_Specular.png"));
		m_pResources->AddTexture("Crystal_Normal", LoadTexture("Data/Textures/Crystal/Crystal_Normal.png"));

		// Menu Textures
		m_pResources->AddTexture("PlayButton", LoadTexture("Data/Textures/MenuButtons/PlayButton.png"));//
        m_pResources->AddTexture("OptionButton", LoadTexture("Data/Textures/MenuButtons/OptionButton.png"));//
        m_pResources->AddTexture("QuitButton", LoadTexture("Data/Textures/MenuButtons/QuitButton.png")); //
        m_pResources->AddTexture("BackButton", LoadTexture("Data/Textures/MenuButtons/BackButton.png"));
        m_pResources->AddTexture("LevelOneButton", LoadTexture("Data/Textures/MenuButtons/LevelOneButton.png"));
        m_pResources->AddTexture("LevelTwoButton", LoadTexture("Data/Textures/MenuButtons/LevelTwoButton.png"));
        m_pResources->AddTexture("BlueButton", LoadTexture("Data/Textures/MenuButtons/BlueButton.png"));
        m_pResources->AddTexture("SaladButton", LoadTexture("Data/Textures/MenuButtons/SaladButton.png"));
        m_pResources->AddTexture("VolumeOnButton", LoadTexture("Data/Textures/MenuButtons/VolumeOnButton.png"));
        m_pResources->AddTexture("VolumeOffButton", LoadTexture("Data/Textures/MenuButtons/VolumeOffButton.png"));
        m_pResources->AddTexture("Star", LoadTexture("Data/Textures/MenuButtons/Star.png"));
        m_pResources->AddTexture("MenuBackground", LoadTexture("Data/Textures/MenuButtons/MainMenu.png"));
        m_pResources->AddTexture("OptionsMenuBackground", LoadTexture("Data/Textures/MenuButtons/OptionsMenu.png"));
	}
	else if (step == LoadingStep_Materials)
	{
		// Load color materials
		m_pResources->AddMaterial("RedColor", new Material(m_pResources->GetShader("LitColor"), MyColor(255, 0, 0, 255), 0.5));

		// Load 3D texture materials
		m_pResources->AddMaterial("Cobblestone", new Material(m_pResources->GetShader("LitTexture"), m_pResources->GetTexture("Cobblestone_Diffuse"), m_pResources->GetTexture("Cobblestone_Specular"), m_pResources->GetTexture("Cobblestone_Normal"), 10));
		m_pResources->AddMaterial("Brick", new Material(m_pResources->GetShader("LitTexture"), m_pResources->GetTexture("Brick_Diffuse"), m_pResources->GetTexture("Brick_Specular"), m_pResources->GetTexture("Brick_Normal"), 10));
		m_pResources->AddMaterial("Stone", new Material(m_pResources->GetShader("LitTexture"), m_pResources->GetTexture("Stone_Diffuse"), m_pResources->GetTexture("Stone_Specular"), m_pResources->GetTexture("Stone_Normal"), 10));
		m_pResources->AddMaterial("StoneWall", new Material(m_pResources->GetShader("LitTexture"), m_pResources->GetTexture("StoneWall_Diffuse"), m_pResources->GetTexture("StoneWall_Specular"), m_pResources->GetTexture("StoneWall_Normal"), 10));
		m_pResources->AddMaterial("Crystal", new Material(m_pResources->GetShader("LitReflectiveTexture"), m_pResources->GetTexture("Crystal_Diffuse"), m_pResources->GetTexture("Crystal_Specular"), m_pResources->GetTexture("Crystal_Normal"), m_pResources->GetTexture("Skybox_Cubemap"), 128));
		m_pResources->AddMaterial("Snow", new Material(m_pResources->GetShader("LitTexture"), m_pResources->GetTexture("Snow_Diffuse"), m_pResources->GetTexture("Snow_Specular"), m_pResources->GetTexture("Snow_Normal"), 32));

		// Load flat texture materials
		m_pResources->AddMaterial("PlayButton", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("PlayButton")));	
        m_pResources->AddMaterial("OptionButton", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("OptionButton")));
        m_pResources->AddMaterial("QuitButton", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("QuitButton")));
        m_pResources->AddMaterial("BackButton", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("BackButton")));
        m_pResources->AddMaterial("LevelOneButton", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("LevelOneButton")));
        m_pResources->AddMaterial("LevelTwoButton", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("LevelTwoButton")));
        m_pResources->AddMaterial("SaladButton", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("SaladButton")));
        m_pResources->AddMaterial("BlueButton", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("BlueButton")));
        m_pResources->AddMaterial("VolumeOnButton", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("VolumeOnButton")));
        m_pResources->AddMaterial("VolumeOffButton", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("VolumeOffButton")));
        m_pResources->AddMaterial("Star", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Star")));
        m_pResources->AddMaterial("Skybox_Cubemap", new Material(m_pResources->GetShader("Cubemap"), m_pResources->GetTexture("Brick_Diffuse"), m_pResources->GetTexture("Skybox_Cubemap")));
        m_pResources->AddMaterial("MenuBackground", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("MenuBackground")));
        m_pResources->AddMaterial("OptionsMenuBackground", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("OptionsMenuBackground")));

	}
	else if (step == LoadingStep_Scenes)
	{
		// Load scenes
		m_pSceneManager->LoadScene("Options", new OptionsScene(m_pSceneManager, m_pResources));
		m_pSceneManager->LoadScene("GameOver", new GameOverScene(m_pSceneManager, m_pResources));
		m_pSceneManager->LoadScene("Pause", new PauseScene(m_pSceneManager, m_pResources));
		m_pSceneManager->LoadScene("LevelSelect", new LevelSelectScene(m_pSceneManager, m_pResources));
		m_pSceneManager->LoadScene("MainMenu", new MainMenuScene(m_pSceneManager, m_pResources));
		m_pSceneManager->LoadScene("LevelOne", new LevelOneScene(m_pSceneManager, m_pResources));
        m_pSceneManager->LoadScene("LevelTwo", new LevelTwoScene(m_pSceneManager, m_pResources));

		m_pSceneManager->LoadScene("HUD", new HUDScene(m_pSceneManager, m_pResources));
	}
	else if (step == LoadingStep_NumberOfSteps)
	{
		FinishLoading();
	}
    else
    {
        return;
    }

    // Increment loading step
	m_CurrentLoadingStep = (LoadingStep)(m_CurrentLoadingStep + 1);
    
    // Calculate loading bar end position and update the uniform
	m_LoadingBarProgressPosition = (m_pGameObjects["LoadingBar_Background"]->GetPosition().x - (m_pGameObjects["LoadingBar_Background"]->GetScale().x / 2.0f)) + (m_CurrentLoadingStep / (float)LoadingStep_NumberOfSteps) * m_pGameObjects["LoadingBar_Background"]->GetScale().x;
    m_pGameObjects["LoadingBar_Bar"]->GetMesh()->SetupUniform1f(m_pGameObjects["LoadingBar_Bar"]->GetMaterial()->GetShader(), "u_LoadingBarProgress", m_LoadingBarProgressPosition);
}

void LoadingScene::FinishLoading()
{
    m_pSceneManager->GetGame()->QueueEvent(new PopSceneEvent(true));
    m_pSceneManager->GetGame()->QueueEvent(new PushSceneEvent("MainMenu"));
}