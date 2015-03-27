#ifndef __MAGICITE_GAME_CONTACT__
#define __MAGICITE_GAME_CONTACT__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "MagiciteGamePhysics.h"
#include <map>

class MagiciteGameObject;
class MagiciteGameLiving;
class MagiciteGameMoveAbleLiving;
class MagiciteItem;

namespace MagiciteGameContact
{

    void change_moveable_direction(MagiciteGameMoveAbleLiving* moveObj);
    /*改变生物移动方向*/

    void try_to_change_living_direction(MagiciteGameLiving* living);
    /*尝试改变生物移动方向*/

    enum ContactType : int
    {
        Cancle = 0,
        Contact,
        Calcture,
        Calture_Cancle,
    };

    extern std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, ContactType>>                                                      judge_contact;
    extern std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, bool>>                                                             judge_contact_end;
    extern std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, std::function<void(MagiciteGameObject*, MagiciteGameObject*)>>>    on_contact;
    extern std::map<Magicite::FIXTURE_TYPE, std::map<Magicite::FIXTURE_TYPE, std::function<void(MagiciteGameObject*, MagiciteGameObject*)>>>    on_contact_end;


    void try_living_contact_with_ground(MagiciteGameObject*, MagiciteGameObject*);
    void try_player_contact_with_enemy(MagiciteGameObject*, MagiciteGameObject*);
    void try_enemy_contact_with_hole(MagiciteGameObject*, MagiciteGameObject*);
    void try_player_contact_with_pitfall(MagiciteGameObject*, MagiciteGameObject*);
    void try_friend_contact_with_pitfall(MagiciteGameObject*, MagiciteGameObject*);
    void try_friend_contact_with_enemy(MagiciteGameObject*, MagiciteGameObject*);
    void try_enemy_contact_with_enemy(MagiciteGameObject*, MagiciteGameObject*);
    void try_player_contact_with_end(MagiciteGameObject*, MagiciteGameObject*);
    void try_ammo_contact_with_enemy(MagiciteGameObject*, MagiciteGameObject*);
    void try_ammo_contact_with_ground(MagiciteGameObject*, MagiciteGameObject*);
    void try_ammo_contact_with_edge(MagiciteGameObject*, MagiciteGameObject*);
    void try_living_contact_with_edge(MagiciteGameObject*, MagiciteGameObject*);
    void try_player_contact_with_item(MagiciteGameObject*, MagiciteGameObject*);
    void try_player_contact_with_protal(MagiciteGameObject*, MagiciteGameObject*);
    void try_player_contact_ground(MagiciteGameObject*, MagiciteGameObject*);
    void try_jump_point_contact_ground(MagiciteGameObject*, MagiciteGameObject*);
    void try_player_leave_ground(MagiciteGameObject*, MagiciteGameObject*);

    bool solve_one_side_platform(b2Body* player, b2Body* platform);

    extern std::function<void(void)>                       _onWin;
    extern std::function<void(void)>                       _onOver;
    extern std::function<void(MagiciteItem*)>              _onPick;
    extern std::function<ContactType(b2Contact* contact)>           _onJudgeContact;
    extern std::function<void(b2Contact* contact)>                  _onBeginContact;
    extern std::function<void(b2Contact* contace)>                  _onEndContact;

    void onWin();
    void onOver();

    void resiger_contact();
}

#endif //__MAGICITE_GAME_CONTACT__