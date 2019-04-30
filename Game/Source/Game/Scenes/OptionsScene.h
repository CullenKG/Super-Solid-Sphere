#ifndef __OptionsScene_H__
#define __OptionsScene_H__

class OptionsScene : public Scene
{
public:
	OptionsScene(SceneManager* pSceneManager, ResourceManager* pResources);
	virtual ~OptionsScene();

	virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
	virtual void LoadContent();

	virtual void Update(float deltatime);
	virtual void Draw();
};

#endif // __OptionsScene_H__
