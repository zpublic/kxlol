#ifndef __MAGICITE_GAME_CONTACT_LISTENER__
#define __MAGICITE_GAME_CONTACT_LISTENER__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

class MagiciteGameContactListener : public b2ContactListener
{
private:
    virtual void BeginContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void EndContact(b2Contact* contact);

    std::function<void(b2Contact* contact)>     _onBeginContact;
public:
    static MagiciteGameContactListener* create(const std::function<void(b2Contact* contact)> &f);
    
    virtual bool init(const std::function<void(b2Contact* contact)> &f);
};

#endif //__MAGICITE_GAME_CONTACT_LISTENER__