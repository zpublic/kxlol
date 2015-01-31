#ifndef __MAGICITE_GAME_CONTACT_LISTENER__
#define __MAGICITE_GAME_CONTACT_LISTENER__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "MagiciteGameLiving.h"
#include "MagiciteGameEnemyManager.h"
#include "MagiciteGamePlayer.h"
#include "MagiciteGameEnemy.h"

class MagiciteGameContactListener : public b2ContactListener
{
private:
    virtual void BeginContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    virtual void EndContact(b2Contact* contact);

    std::function<void(void)>                   _failed;
    MagiciteGameEnemyManager*                   _manager;
public:
    static MagiciteGameContactListener* create(MagiciteGameEnemyManager* manager, const std::function<void(void)> &failed);
    virtual bool init(MagiciteGameEnemyManager* manager,const std::function<void(void)> &failed);
};

#endif //__MAGICITE_GAME_CONTACT_LISTENER__