#ifndef __PushSceneEvent_H__
#define __PushSceneEvent_H__

class PushSceneEvent : public Event
{
protected:
    std::string m_Scene;

public:
    PushSceneEvent(std::string scene)
    {
        m_EventType = EventType_PushScene;
        m_Scene = scene;
    }

    std::string GetSceneName() { return m_Scene; }
};

#endif //__PushSceneEvent_H__