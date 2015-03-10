#ifndef __MAGICITE_GAME_LAYER_H__
#define __MAGICITE_GAME_LAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MagiciteGameMap;
class MagiciteGamePhyLayer;
class MagiciteGamePlayer;
class MagiciteGameControlAble;
class MagiciteWeather;

class MagiciteGameLayer : public cocos2d::Layer
{
public:
    enum UITAG
    {
        PACK = 100,
        EQUIP
    };
    MagiciteGameLayer();
    ~MagiciteGameLayer();

    virtual bool init();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onOnBeginContact(b2Contact* contact);
    bool onOnJudgeContact(b2Contact* contact);

    CREATE_FUNC(MagiciteGameLayer);

	void update(float timeDelta);

    void init_contact();

    void create_end_cube(cocos2d::TMXObjectGroup*);
    void create_player(cocos2d::TMXObjectGroup*);
    void create_enemy(cocos2d::TMXObjectGroup*);
    void create_pitfall(cocos2d::TMXObjectGroup*);
    void create_ground(cocos2d::TMXObjectGroup*);
    void create_NPC(cocos2d::TMXObjectGroup*);

    void use_weather(MagiciteWeather* weather);

private:
    MagiciteGamePlayer*                 _player;
    MagiciteGamePhyLayer*               _phyLayer;
    MagiciteGameMap*                    _background;
    cocos2d::Size                       _visibleSize;
    cocos2d::Vec2                       _origin;

};

#endif // __MAGICITE_GAME_LAYER_H__
