#ifndef __PauseScene_H__
#define __PauseScene_H__

class PauseScene : public Scene
{
public:
	PauseScene(SceneManager* pSceneManager, ResourceManager* pResources);
	virtual ~PauseScene();

	virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
	virtual void LoadContent();

	virtual void Update(float deltatime);
	virtual void Draw();
};

#endif // __PauseScene_H__
