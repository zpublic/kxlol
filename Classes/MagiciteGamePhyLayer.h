#ifndef __MAGICITE_GAME_PHY_LAYER__
#define __MAGICITE_GAME_PHY_LAYER__

class MagiciteGameEnemyManager;

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"
#include "MagiciteGamePhySprite.h"
#include "MagiciteGameContactListener.h"

class MagiciteGamePhyLayer : public cocos2d::Layer
{
public:
    MagiciteGamePhyLayer();
    ~MagiciteGamePhyLayer();

    static const int PTM_RATIO = 32;

    bool initPhysics(MagiciteGameEnemyManager* manager, cocos2d::Size);
    void addPhysicSprite(MagiciteGamePhySprite* ptr, bool is_static);

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    void update(float timeDelta);

    static MagiciteGamePhyLayer* create(MagiciteGameEnemyManager* manager, cocos2d::Size size);

private:
    MagiciteGameContactListener*        _contactListener;
    cocos2d::Size                       _visibleSize;
    b2World*                            _world;
    b2Body*                             _body;
    GLESDebugDraw*                      _debugDraw;
};

#endif //__MAGICITE_GAME_PHY_LAYER__