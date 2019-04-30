#ifndef __Event_H__
#define __Event_H__

enum EventTypes
{
    EventType_Input,
    EventType_PushScene,
    EventType_PopScene,
	EventType_Reset,
    EventType_DeactiveTween,
    EventType_NotSet,
};

class Event
{
protected:
    EventTypes m_EventType;

public:
    Event()
    {
        m_EventType = EventType_NotSet;
    }
    virtual ~Event() {}

    EventTypes GetEventType() { return m_EventType; }
};

#endif //__Event_H__