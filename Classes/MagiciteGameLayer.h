#ifndef __MAGICITE_GAME_LAYER_H__
#define __MAGICITE_GAME_LAYER_H__

#include "cocos2d.h"
#include "MagiciteGameMap.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGamePause.h"
#include "MagiciteGameOver.h"
#include "MagiciteGameWin.h"
#include "MagiciteGamePlayer.h"
#include "MagiciteGameEnemyManager.h"
#include "MagiciteGamePitfallManager.h"
#include "MagiciteGameFriendManager.h"
#include "MagiciteGameContact.h"
#include "MagiciteGameControlAble.h"
#include "MagiciteGameFireball.h"

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

    void try_living_contact_with_ground(MagiciteGameObject*, MagiciteGameObject*);
    void try_player_contact_with_enemy(MagiciteGameObject*, MagiciteGameObject*);
    void try_player_contact_with_pitfall(MagiciteGameObject*, MagiciteGameObject*);
    void try_friend_contact_with_pitfall(MagiciteGameObject*, MagiciteGameObject*);
    void try_friend_contact_with_enemy(MagiciteGameObject*, MagiciteGameObject*);
    void try_enemy_contact_with_enemy(MagiciteGameObject*, MagiciteGameObject*);
    void try_player_contact_with_end(MagiciteGameObject*, MagiciteGameObject*);
    void try_ammo_contact_with_enemy(MagiciteGameObject*, MagiciteGameObject*);
    void try_ammo_contact_with_ground(MagiciteGameObject*, MagiciteGameObject*);
    void try_ammo_contact_with_edge(MagiciteGameObject*, MagiciteGameObject*);
    void try_living_contact_with_edge(MagiciteGameObject*, MagiciteGameObject*);

    void init_contact();

    //void create_pitfall_with_tiled();
    void create_end_cube(cocos2d::TMXObjectGroup*);
    void create_player(cocos2d::TMXObjectGroup*);
    void create_enemy(cocos2d::TMXObjectGroup*);
    void create_pitfall(cocos2d::TMXObjectGroup*);
    void create_ground(cocos2d::TMXObjectGroup*);



private:
    MagiciteGameEnemyManager*           _enemyManager;
    MagiciteGamePitfallManager*         _pitfallManager;
    MagiciteGameFriendManager*          _friendManager;
    MagiciteGamePlayer*                 _player;
    MagiciteGamePhyLayer*               _phyLayer;
    MagiciteGameMap*                    _background;
    cocos2d::Size                       _visibleSize;
    cocos2d::Vec2                       _origin;

};

#endif // __MAGICITE_GAME_LAYER_H__
