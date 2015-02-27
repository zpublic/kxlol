#ifndef __MAGICITE_GAME_PHY_WORLD__
#define __MAGICITE_GAME_PHY_WORLD__

#include "Box2D/Box2D.h"
#include "cocos2d.h"

class MagiciteGameObject;
class MagiciteGameContactListener;

class MagiciteGamePhyWorld : public b2World
{
public:
    MagiciteGamePhyWorld(b2Vec2 gravity);
    ~MagiciteGamePhyWorld();

    static const int PTM_RATIO = 32;

    void createPhyBody(MagiciteGameObject* ptr, bool is_static, uint16 Category, uint16 mask);
    void updateBody();

    bool init(cocos2d::Size size, const std::function<void(b2Contact*)> &contactFunc);
    static MagiciteGamePhyWorld* create(b2Vec2 gravity, cocos2d::Size size, const std::function<void(b2Contact*)> &contactFunc);

private:
    MagiciteGameContactListener*        _contactListener;
};

#endif //__MAGICITE_GAME_PHY_WORLD__