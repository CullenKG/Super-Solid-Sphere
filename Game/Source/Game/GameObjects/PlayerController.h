#ifndef __PlayerController_H__
#define __PlayerController_H__

enum PlayerControllerButtons
{
    PCB_Up    = 0x00000001,
    PCB_Down  = 0x00000002,
    PCB_Left  = 0x00000004,
    PCB_Right = 0x00000008,
    PCB_LeftMouse = 0x00000010,
	PCB_R = 0x00000020, 
	PCB_Q = 0x00000040,
	PCB_E = 0x00000080,
	PCB_P = 0x00000100
};

class PlayerController
{
protected:
    unsigned int m_ButtonFlags;
    unsigned int m_LastButtonFlags;

    vec2 m_MouseLocation;

public:
    PlayerController();
    virtual ~PlayerController();

    void Clear();

    void Update(float deltatime);

    void SetButtonPressed(PlayerControllerButtons button);
    void SetButtonReleased(PlayerControllerButtons button);

    bool IsButtonPressed(PlayerControllerButtons button);
    bool IsButtonHeld(PlayerControllerButtons button);

    vec2 GetMouseLocation() { return m_MouseLocation; }

    void OnEvent(Event* pEvent);
};

#endif //__PlayerController_H__
