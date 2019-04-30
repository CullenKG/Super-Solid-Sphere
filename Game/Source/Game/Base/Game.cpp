#include "GamePCH.h"

Game::Game(Framework* pFramework)
	: GameCore(pFramework)
{
	m_pImGuiManager = 0;

	m_WindowWidth = -1;
	m_WindowHeight = -1;

	m_pSceneManager = 0;
	m_pResources = 0;
}

Game::~Game()
{
	while (m_EventQueue.size() != 0)
	{
		Event* pEvent = m_EventQueue.front();
		m_EventQueue.pop();
		delete pEvent;
	}

	delete m_pSceneManager;
	delete m_pTweenManager;
	delete m_pResources;
	delete m_pImGuiManager;
}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
	glViewport(0, 0, width, height);

	m_WindowWidth = width;
	m_WindowHeight = height;
}

void Game::LoadContent()
{
	// Seed random.
	srand((unsigned int)GetSystemTime());

	CheckForGLErrors();

	// Turn on depth buffer testing.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// Turn on alpha blending.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Turn on back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	// Create the resource manager
	m_pResources = new ResourceManager();

	// Create the scene manager
	m_pSceneManager = new SceneManager(this);

	// Create the tween manager
	m_pTweenManager = new TweenManager(this);

	// Create the loading scene
	m_pSceneManager->LoadScene("Loading", new LoadingScene(m_pSceneManager, m_pResources));
	m_pSceneManager->PushScene("Loading");

	m_pImGuiManager = new ImGuiManager();
	m_pImGuiManager->Init();

	CheckForGLErrors();
}

void Game::QueueEvent(Event* pEvent)
{
	m_EventQueue.push(pEvent);
}

void Game::ProcessEvents()
{
	while (m_EventQueue.size() != 0)
	{
		Event* pEvent = m_EventQueue.front();
		m_EventQueue.pop();

		OnEvent(pEvent);
		delete pEvent;
	}
}

void Game::OnEvent(Event* pEvent)
{
	m_pImGuiManager->OnEvent(pEvent);

	m_pSceneManager->OnEvent(pEvent);

	m_Controllers[0].OnEvent(pEvent);
}

void Game::Update(float deltatime)
{
	// Process events at the start of the frame before updating anything else in the game.
	ProcessEvents();

	// Once our events are processes, tell imgui we're starting a new frame.
	m_pImGuiManager->StartFrame((float)m_WindowWidth, (float)m_WindowHeight, deltatime);

	m_pTweenManager->Update(deltatime);

	m_pSceneManager->Update(deltatime);

    m_Controllers[0].Update(deltatime);
}

void Game::Draw()
{
	// Clear the screen to dark blue.
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the scene
	m_pSceneManager->Draw();

	CheckForGLErrors();

	// Tell imgui we're at the end of our frame, so it will draw all queued objects.
	m_pImGuiManager->EndFrame();

	CheckForGLErrors();
}