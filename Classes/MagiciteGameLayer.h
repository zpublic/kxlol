#ifndef __MAGICITE_GAME_LAYER_H__
#define __MAGICITE_GAME_LAYER_H__

#include "cocos2d.h"
#include "MagiciteGameMap.h"
#include "MagiciteGamePhySprite.h"
#include "MagiciteGamePhyLayer.h"
#include "Box2D\Box2D.h"

class MagiciteGameLayer : public cocos2d::Layer
{
public:

    virtual bool init();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    CREATE_FUNC(MagiciteGameLayer);

	void update(float timeDelta);

private:
    MagiciteGamePhyLayer*   _phyLayer;
    MagiciteGamePhySprite*  _player;
    MagiciteGameMap*        _background;
    cocos2d::Size           _visibleSize;
    cocos2d::Vec2           _origin;
    bool                    _move_left;
    bool                    _move_right;
};

#endif // __MAGICITE_GAME_LAYER_H__