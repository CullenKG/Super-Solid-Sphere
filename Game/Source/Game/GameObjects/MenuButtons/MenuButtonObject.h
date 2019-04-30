#ifndef __MenuButtonObject_H__
#define __MenuButtonObject_H__

class MenuButtonObject : public GameObject
{
protected:
	SoundPlayer* m_pSoundPlayer;

	vec3 m_InitialScale;

	TweenObject* m_Tween;
	float m_CurrentTweenScale;

	bool m_IsMouseOver;

public:
	MenuButtonObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
	MenuButtonObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname);
	virtual ~MenuButtonObject();

	virtual void Update(float deltatime);

	bool IsMouseOver(vec2 mousePosition);
};

#endif //__MenuButtonObject_H__
