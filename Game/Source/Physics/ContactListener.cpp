#include "GamePCH.h"

ContactListener::ContactListener(BulletWorld * world)
{
    m_pBulletWorld = world;
}

ContactListener::~ContactListener()
{
}

void ContactListener::Update(float deltatime)
{
    for (int i = 0; i < m_pBulletWorld->GetDynamicsWorld()->getDispatcher()->getNumManifolds(); i++)
    {
        btPersistentManifold* contactManifold = m_pBulletWorld->GetDynamicsWorld()->getDispatcher()->getManifoldByIndexInternal(i);

        if (contactManifold->getNumContacts() > 0)
        {
            const btCollisionObject* objectA = contactManifold->getBody0();
            const btCollisionObject* objectB = contactManifold->getBody1();

            GameObject* gameobjectA = (GameObject*)objectA->getUserPointer();
            GameObject* gameobjectB = (GameObject*)objectB->getUserPointer();

            gameobjectA->BeginContact(gameobjectB);
            gameobjectB->BeginContact(gameobjectA);
        }
    }
}
