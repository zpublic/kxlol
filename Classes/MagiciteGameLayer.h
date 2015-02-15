#ifndef __MAGICITE_GAME_LAYER_H__
#define __MAGICITE_GAME_LAYER_H__

#include "cocos2d.h"
#include "MagiciteGameMap.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGamePause.h"
#include "MagiciteGameOver.h"
#include "MagiciteGameWin.h"
#include "MagiciteGamePlayer.h"
#include "MagiciteGameContact.h"
#include "MagiciteGameControlAble.h"
#include "MagiciteGaemFactoryMethod.h"

class MagiciteGameLayer : public cocos2d::Layer
{
public:
    MagiciteGameLayer();
    ~MagiciteGameLayer();

    typedef MagiciteGameObject::_entityCategory   Category;

    virtual bool init();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onOnBeginContact(b2Contact* contact);

    CREATE_FUNC(MagiciteGameLayer);

	void update(float timeDelta);

    void init_contact();

    void create_end_cube(cocos2d::TMXObjectGroup*);
    void create_player(cocos2d::TMXObjectGroup*);
    void create_enemy(cocos2d::TMXObjectGroup*);
    void create_pitfall(cocos2d::TMXObjectGroup*);
    void create_ground(cocos2d::TMXObjectGroup*);

private:
    MagiciteGamePlayer*                 _player;
    MagiciteGamePhyLayer*               _phyLayer;
    MagiciteGameMap*                    _background;
    cocos2d::Size                       _visibleSize;
    cocos2d::Vec2                       _origin;

};

#endif // __MAGICITE_GAME_LAYER_H__
