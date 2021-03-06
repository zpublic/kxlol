#ifndef __MAGICITE_GAME_PHY_WORLD__
#define __MAGICITE_GAME_PHY_WORLD__

#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "MagiciteGamePhysics.h"

class MagiciteGameObject;
class MagiciteGameContactListener;

class MagiciteGamePhyWorld : public b2World
{
public:
    MagiciteGamePhyWorld(b2Vec2 gravity);
    ~MagiciteGamePhyWorld();

    void createPhyBody(MagiciteGameObject* ptr, bool is_static, Magicite::FIXTURE_TYPE type);
    b2Body* createBody(b2BodyDef* bd);
    void updateBody(float timeDelta);

    bool init(cocos2d::Size size);
    static MagiciteGamePhyWorld* create(b2Vec2 gravity, cocos2d::Size size);

private:
    MagiciteGameContactListener*        _contactListener;
};

#endif //__MAGICITE_GAME_PHY_WORLD__