#ifndef __MAGICITE_GAME_CONTACT__
#define __MAGICITE_GAME_CONTACT__

#include "cocos2d.h"
#include "MagiciteGameObject.h"
#include "MagiciteGameLiving.h"
#include "MagiciteGameMoveAbleLiving.h"


namespace MagiciteGameContact
{
    MagiciteGameObject* trivialGround(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    bool try_moveable_contact_with_grond(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    void change_moveable_direction(MagiciteGameMoveAbleLiving* moveObj);
    bool is_moveable_on_ground(MagiciteGameMoveAbleLiving* moveObj, MagiciteGameObject* ground);
    bool is_moveable_above_ground(MagiciteGameMoveAbleLiving* moveObj, MagiciteGameObject* ground);
    bool try_enemy_contact_with_living(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    MagiciteGameLiving* trivialEnemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    void try_to_change_living_direction(MagiciteGameLiving* living);

}

#endif //__MAGICITE_GAME_CONTACT__