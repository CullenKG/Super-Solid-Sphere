#include "GamePCH.h"

SampleScene::SampleScene(SceneManager* pSceneManager, ResourceManager* pResources)
    : Scene(pSceneManager, pResources)
{
}

SampleScene::~SampleScene()
{
}

void SampleScene::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    Scene::OnSurfaceChanged(width, height);
}

void SampleScene::LoadContent()
{
  //  m_pBulletWorld = new BulletWorld();

  //  Scene::LoadContent();

  //  // Load our shaders.
  //  {
		//m_pResources->AddShader("LitTexture", new ShaderProgram("Data/Shaders/LitTexture.vert", "Data/Shaders/LitTexture.frag"));
		//m_pResources->AddShader("LitColor", new ShaderProgram("Data/Shaders/LitColor.vert", "Data/Shaders/LitColor.frag"));
  //  }

  //  // Create meshes.
  //  {
  //      m_pResources->AddMesh("Sphere", Mesh::LoadObject("Data/Objects/sphere2.obj"));
  //      m_pResources->AddMesh("CubeObject", Mesh::LoadObject("Data/Objects/cube.obj"));
  //  }

  //  // Load our textures.
  //  {
  //      // Cobblestone texture
  //      m_pResources->AddTexture("Cobblestone_Diffuse", LoadTexture("Data/Textures/Cobblestone/Cobblestone_Diffuse.png"));
  //      m_pResources->AddTexture("Cobblestone_Specular", LoadTexture("Data/Textures/Cobblestone/Cobblestone_Specular.png"));
  //      m_pResources->AddTexture("Cobblestone_Normal", LoadTexture("Data/Textures/Cobblestone/Cobblestone_Normal.png"));

  //      // Brick texture
  //      m_pResources->AddTexture("Brick_Diffuse", LoadTexture("Data/Textures/Brick/Brick_Diffuse.png"));
  //      m_pResources->AddTexture("Brick_Specular", LoadTexture("Data/Textures/Brick/Brick_Specular.png"));
  //      m_pResources->AddTexture("Brick_Normal", LoadTexture("Data/Textures/Brick/Brick_Normal.png"));

  //      // Stone texture
  //      m_pResources->AddTexture("Stone_Diffuse", LoadTexture("Data/Textures/Stone/Stone_Diffuse.png"));
  //      m_pResources->AddTexture("Stone_Specular", LoadTexture("Data/Textures/Stone/Stone_Specular.png"));
  //      m_pResources->AddTexture("Stone_Normal", LoadTexture("Data/Textures/Stone/Stone_Normal.png"));

		//// Crystal texture
		//m_pResources->AddTexture("Crystal_Diffuse", LoadTexture("Data/Textures/Crystal/Crystal_Diffuse.png"));
		//m_pResources->AddTexture("Crystal_Specular", LoadTexture("Data/Textures/Crystal/Crystal_Specular.png"));
		//m_pResources->AddTexture("Crystal_Normal", LoadTexture("Data/Textures/Crystal/Crystal_Normal.png"));
  //  }

  //  // Create our materials.
  //  {
		//// cubemap

  //      //const char** filenames = new const char*[6];

  //      //filenames[0] = "Data/Textures/posx.png";
  //      //filenames[1] = "Data/Textures/negx.png";
  //      //filenames[2] = "Data/Textures/posy.png";
  //      //filenames[3] = "Data/Textures/negy.png";
  //      //filenames[4] = "Data/Textures/posz.png";
  //      //filenames[5] = "Data/Textures/negz.png"; 

		//m_pResources->AddMaterial("RedColor", new Material(m_pResources->GetShader("LitColor"), MyColor(255, 0, 0, 255), 0.5));

  //      m_pResources->AddMaterial("Cobblestone", new Material(m_pResources->GetShader("LitTexture"), m_pResources->GetTexture("Cobblestone_Diffuse"), m_pResources->GetTexture("Cobblestone_Specular"), m_pResources->GetTexture("Cobblestone_Normal"), 10));
  //      m_pResources->AddMaterial("Brick", new Material(m_pResources->GetShader("LitTexture"), m_pResources->GetTexture("Brick_Diffuse"), m_pResources->GetTexture("Brick_Specular"), m_pResources->GetTexture("Brick_Normal"), 10));
  //      m_pResources->AddMaterial("Stone", new Material(m_pResources->GetShader("LitTexture"), m_pResources->GetTexture("Stone_Diffuse"), m_pResources->GetTexture("Stone_Specular"), m_pResources->GetTexture("Stone_Normal"), 10));
  //      m_pResources->AddMaterial("Crystal", new Material(m_pResources->GetShader("LitTexture"), m_pResources->GetTexture("Crystal_Diffuse"), m_pResources->GetTexture("Crystal_Specular"), m_pResources->GetTexture("Crystal_Normal"), 128));
  //      //delete[] filenames;
  //  }

  //  // Create some game objects.
  //  {
  //      // Camera
  //      m_pGameObjects["Camera"] = new CameraObject(this, "Camera", vec3(0, -2.5, 3), vec3(0, 0, 0), vec3(1, 1, 1));
  //      m_pGameObjects["Camera"]->SetRotation(vec3(-15.0f, 0.0f, 0.0f));

		////m_pGameObjects["SkyboxSorta"] = new GameObject(this, "SkyboxSorta", vec3(0, 0, 0), vec3(0, 0, 0), vec3(1.0f, 1.0f, 1.0f), "Background", "Sky");

		//// Point lights
  //      m_pLights["DirectionalLight"] = new DirectionalLight(this, "DirectionalLight", vec3(0, 1, 0), vec3(0, -1, 0));
  //      m_pLights["DirectionalLight"]->SetLightColor(vec3(0.3f, 0.3f, 0.3f), vec3(0.4f, 0.4f, 0.4f), vec3(0.5f, 0.5f, 0.5f));

		//m_pLights["PointLight1"] = new PointLight(this, "PointLight1", vec3(0, 3, 0), 1.0f, 0.09f, 0.032f);
		//m_pLights["PointLight1"]->SetLightColor(vec3(0.2f, 0.2f, 0.2f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f));

  //      //m_pLights["PointLight2"] = new PointLight(this, "PointLight2", vec3(0, 2, 5), 1.0f, 0.09f, 0.032f);
  //      //m_pLights["PointLight2"]->SetLightColor(vec3(0.2f, 0.2f, 0.2f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f));

  //      // Player
  //      m_pGameObjects["Player"] = new PlayerObject(this, "Player", vec3(0, 0.5, 0), vec3(0, 0, 0), vec3(1.0, 1.0f, 1.0f), "Sphere", "Crystal");
  //      m_pGameObjects["Player"]->CreateSphereBody(1.0f, 0.5f);
  //      ((PlayerObject*)m_pGameObjects["Player"])->SetController(m_pGame->GetController(0));
		//((CameraObject*)m_pGameObjects["Camera"])->SetObjectToFollow(m_pGameObjects["Player"]);


  //      // Ground
  //      m_pGameObjects["Ground"] = new GameObject(this, "Ground", vec3(0, -2.5, 0), vec3(0, 0, 0), vec3(5, 5, 5), "CubeObject", "Brick");
  //      m_pGameObjects["Ground"]->CreateBoxBody(0.0f);
  //  }
}

void SampleScene::Update(float deltatime)
{
    Scene::Update(deltatime);

    //m_pGameObjects["SkyboxSorta"]->SetPosition(m_pGameObjects["Player"]->GetPosition());

	//if (m_pGame->GetController(0)->IsButtonPressed(PCB_Left))
	//{
	//	//m_pGameObjects["Camera"]->SetRotation(m_pGameObjects["Camera"]->GetRotation() + (vec3(0, -45.0f, 0) * deltatime));
	//}

	//if (m_pGame->GetController(0)->IsButtonPressed(PCB_Right))
	//{
	//	//m_pGameObjects["Camera"]->SetRotation(m_pGameObjects["Camera"]->GetRotation() + (vec3(0, 45.0f, 0) * deltatime));
	//}

 //   if (m_pGame->GetController(0)->IsButtonPressed(PCB_Up))
 //   {
 //       //m_pGameObjects["Camera"]->SetRotation(m_pGameObjects["Camera"]->GetRotation() + (vec3(-45.0f, 0, 0) * deltatime));
 //   }

 //   if (m_pGame->GetController(0)->IsButtonPressed(PCB_Down))
 //   {
 //      //m_pGameObjects["Camera"]->SetRotation(m_pGameObjects["Camera"]->GetRotation() + (vec3(45.0f, 0, 0) * deltatime));
 //   }
}

void SampleScene::Draw()
{
    Scene::Draw();
}
