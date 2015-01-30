#ifndef __MAGICITE_GAME_CONTACT_LISTENER__
#define __MAGICITE_GAME_CONTACT_LISTENER__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "MagiciteGameLiving.h"

class MagiciteGameContactListener : public b2ContactListener
{
private:
    virtual void BeginContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void EndContact(b2Contact* contact);

public:
    static MagiciteGameContactListener* create();
    virtual bool init();
};

#endif //__MAGICITE_GAME_CONTACT_LISTENER__