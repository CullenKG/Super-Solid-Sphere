#ifndef __PopSceneEvent_H__
#define __PopSceneEvent_H__

class PopSceneEvent : public Event
{
protected:
    bool m_PopAllScenes;

public:
    PopSceneEvent(bool popAllScenes)
    {
        m_EventType = EventType_PopScene;
        m_PopAllScenes = popAllScenes;
    }

    bool ShouldPopAllScenes() { return m_PopAllScenes; }

};

#endif //__PopSceneEvent_H__