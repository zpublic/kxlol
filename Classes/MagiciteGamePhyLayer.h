#ifndef __MAGICITE_GAME_PHY_LAYER__
#define __MAGICITE_GAME_PHY_LAYER__

#define MAGICITE_DEBUG_OFF

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"
#include "MagiciteGameObject.h"
#include "MagiciteGamePhyWorld.h"
#include "MagiciteGameMoveAbleLiving.h"

class MagiciteGamePhyLayer : public cocos2d::Layer
{
public:
    MagiciteGamePhyLayer();
    ~MagiciteGamePhyLayer();

    static const int PTM_RATIO = 32;

    bool initPhysics(cocos2d::Size size, const std::function<void(b2Contact*)> &contactFunc);
    void createPhyBody(
        MagiciteGameObject* ptr, 
        bool is_static, 
        uint16 Category = MagiciteGameObject::DEFAULT_GROUND, 
        uint16 mask = MagiciteGameObject::DEFAULT_ALL);

    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags);
    void update(float timeDelta);

    static MagiciteGamePhyLayer* create(cocos2d::Size size, const std::function<void(b2Contact*)> &contactFunc);

    bool Ray_Cast(MagiciteGameMoveAbleLiving* sprite, float length, b2Fixture*& outFix, float& output);

private:
    cocos2d::Size                       _visibleSize;
    MagiciteGamePhyWorld*               _world;
    GLESDebugDraw*                      _debugDraw;
};

#endif //__MAGICITE_GAME_PHY_LAYER__