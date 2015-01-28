#ifndef __MAGICITE_GAME_LAYER_H__
#define __MAGICITE_GAME_LAYER_H__

#include "cocos2d.h"
#include "MagiciteGameMap.h"
#include "MagiciteGamePhySprite.h"
#include "Box2D\Box2D.h"

class MagiciteGameLayer : public cocos2d::Layer
{
public:
    MagiciteGameLayer();
    ~MagiciteGameLayer();

    virtual bool init();
    void initPhysics();
    static const int PTM_RATIO = 32;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    CREATE_FUNC(MagiciteGameLayer);

	void update(float timeDelta);

private:
    MagiciteGamePhySprite*  _player;
    MagiciteGameMap*        _background;
    cocos2d::Size           _visibleSize;
    cocos2d::Vec2           _origin;
    bool                    _move_left;
    bool                    _move_right;
    b2World*                _world;
};

#endif // __MAGICITE_GAME_LAYER_H__
