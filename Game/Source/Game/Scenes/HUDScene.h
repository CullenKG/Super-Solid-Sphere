#ifndef __HUDScene_H__
#define __HUDScene_H__

class HUDScene : public Scene
{
protected:

public:
	HUDScene(SceneManager* pSceneManager, ResourceManager* pResources);
	virtual ~HUDScene();

	virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
	virtual void LoadContent();

	virtual void Update(float deltatime);
	virtual void Draw();
};

#endif // __HUDScene_H__
