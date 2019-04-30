#include "GamePCH.h"

class BulletWorld;

class ContactListener
{
public:
    ContactListener(BulletWorld* world);
    ~ContactListener();

    void Update(float deltatime);
private:
    BulletWorld* m_pBulletWorld;
};