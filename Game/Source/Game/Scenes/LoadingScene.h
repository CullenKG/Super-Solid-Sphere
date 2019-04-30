#ifndef __LoadingScene_H__
#define __LoadingScene_H__

class LoadingScene : public Scene
{
protected:
	enum LoadingStep
	{
		LoadingStep_Shaders,
		LoadingStep_Audio,
		LoadingStep_Meshes,
		LoadingStep_TextureGroup1,
		LoadingStep_TextureGroup2,
		LoadingStep_TextureGroup3,
		LoadingStep_TextureGroup4,
		LoadingStep_Materials,
		LoadingStep_Scenes,
		
		LoadingStep_NumberOfSteps
	};

	LoadingStep m_CurrentLoadingStep;
	float m_LoadingBarProgressPosition;

public:
	LoadingScene(SceneManager* pSceneManager, ResourceManager* pResources);
	virtual ~LoadingScene();

	virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
	virtual void LoadContent();

	virtual void Update(float deltatime);
	virtual void Draw();

	void Load(LoadingStep step);
	void FinishLoading();
};

#endif // __LoadingScene_H__
