#ifndef __CameraObject_H__
#define __CameraObject_H__

class CameraObject : public GameObject
{
protected:
    
    mat4 m_MatView;
    mat4 m_MatViewSkyBox;
    mat4 m_MatProj;
	mat4 m_MatNormal;

    GameObject* m_ObjectToFollow;

	Vector3 m_CurrentRotation;

	Vector3 m_ForwardDirection;
	Vector3 m_RightDirection;

	TweenObject* m_CameraXTween;
	TweenObject* m_CameraYTween;
	TweenObject* m_CameraZTween;

	float m_MovingToX;
	float m_MovingToY;
	float m_MovingToZ;

public:
    CameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale);
    virtual ~CameraObject();

    virtual void Update(float deltatime);

	virtual void Reset();

    mat4* GetViewMatrix() { return &m_MatView; }
    mat4* GetViewSkyBoxMatrix() { return &m_MatViewSkyBox; }
    mat4* GetProjMatrix() { return &m_MatProj; }
	mat4* GetNormalMatrix() { return &m_MatNormal; }

    void SetObjectToFollow(GameObject* object);

	Vector3 GetForwardDirection() { return m_ForwardDirection; }
	Vector3 GetRightDirection() { return m_RightDirection; }
};

#endif //__CameraObject_H__