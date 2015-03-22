#ifndef __MAGICITE_GAME_LAYER_H__
#define __MAGICITE_GAME_LAYER_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class MagiciteGameMap;
class MagiciteGamePhyLayer;
class MagiciteGamePlayer;
class MagiciteGameControlAble;
class MagiciteWeather;
class MagiciteGameMoveAbleManager;

namespace  MagiciteGameContact
{
    enum ContactType : int;
}

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
    MagiciteGameContact::ContactType onOnJudgeContact(b2Contact* contact);

    CREATE_FUNC(MagiciteGameLayer);

	void update(float timeDelta);

    void init_contact();
    void init_map_data(cocos2d::TMXTiledMap*);

    void create_end_cube(cocos2d::TMXObjectGroup*);
    void create_player(cocos2d::TMXObjectGroup*);
    void create_enemy(cocos2d::TMXObjectGroup*);
    void create_pitfall(cocos2d::TMXObjectGroup*);
    void create_ground(cocos2d::TMXObjectGroup*);
    void create_NPC(cocos2d::TMXObjectGroup*);
    void create_item(cocos2d::TMXObjectGroup*);

    void use_weather(MagiciteWeather* weather);

    void showText(const std::string& str);

private:
    MagiciteGameMoveAbleManager*        _moveableManager;
    MagiciteGamePlayer*                 _player;
    MagiciteGamePhyLayer*               _phyLayer;
    MagiciteGameMap*                    _background;
};

#endif // __MAGICITE_GAME_LAYER_H__
