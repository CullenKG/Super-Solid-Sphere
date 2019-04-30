#ifndef __PlayerObject_H__
#define __PlayerObject_H__

class PlayerObject : public GameObject
{
protected:
    PlayerController* m_pController;
	SoundPlayer* m_pSoundPlayer;

    vec2 m_InputDirection;
	vec2 m_PureInputDirection;
	vec2 m_MovementDirection;

    bool m_BeatLevel;

public:
    PlayerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    PlayerObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, std::string meshname, std::string materialname);
    virtual ~PlayerObject();

    void SetController(PlayerController* pController);

    vec2 GetInputDirection();
	vec2 GetMovementDirection();

    void BeginContact(GameObject* other);


	vec2 GetPureInput() { return m_PureInputDirection; }

    virtual void Update(float deltatime);

    bool HasBeatLevel() { return m_BeatLevel; }
};

#endif //__PlayerObject_H__
