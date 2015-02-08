#ifndef __MAGICITE_GAME_CONTACT__
#define __MAGICITE_GAME_CONTACT__

#include "cocos2d.h"
#include "MagiciteGameObject.h"
#include "MagiciteGameLiving.h"
#include "MagiciteGamePitfall.h"
#include "MagiciteGameMoveAbleLiving.h"

namespace MagiciteGameContact
{
    bool is_moveable_on_ground(MagiciteGameMoveAbleLiving* moveObj, MagiciteGameObject* ground);
    /*判断moveObj在ground的正上方或正下方*/

    bool is_moveable_above_ground(MagiciteGameMoveAbleLiving* moveObj, MagiciteGameObject* ground);
    /*判断moveObj在ground的正上方*/

    bool is_all_living(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    /*判断objectA与objectB是否全部为Living类*/

    bool is_have_player(MagiciteGameLiving* livingA, MagiciteGameLiving* livingB);
    /*判断livingA与livingA有没有玩家控制的*/

    MagiciteGameObject* trivialGround(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    /*从objectA与objectB中提取Type为T_Ground的 提取失败返回nullptr*/

    MagiciteGameLiving* trivialEnemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    /*从objectA与objectB中提取Type为T_Living且｛MoveAbleType为NormalLiving（不可移动）的 
        或 MoveAbleType为MoveAbleLiving 但_is_contraled为false（没有玩家控制）的 提取失败返回nullptr*/

    MagiciteGameMoveAbleLiving* trivialPlayer(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    /*从objectA与objectB中提取Type为T_Living且｛MoveAbleType为MoveAbleLiving 且_is_contraled为true（有玩家控制）的
        提取失败返回nullptr*/
    MagiciteGameMoveAbleLiving* trivialFriend(MagiciteGameObject* objectA, MagiciteGameObject* objectB);

    MagiciteGamePitfall* trivialPitfall(MagiciteGameObject* objectA, MagiciteGameObject* objectB);

    bool calc_player_and_enemy(MagiciteGameMoveAbleLiving* objectA, MagiciteGameLiving* objectB);
    /*计算player在enemy的上方 如果是则返回true */

    void change_moveable_direction(MagiciteGameMoveAbleLiving* moveObj);
    /*将moveObj的前进方向置反*/

    void try_to_change_living_direction(MagiciteGameLiving* living);
    /*如果living可移动 则置反它的前进方向*/

    bool try_moveable_contact_with_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    /*提取出可移动的living和ground 如果提取失败返回false 如果提取成功 如果living在ground上方 则将living的jump状态取消
        如果不在living上下方则判断是否有玩家控制 如果没有则置反前进方向*/

    void try_enemy_contact_with_enemy(MagiciteGameLiving* enemyA, MagiciteGameLiving* enemyB);
    /*尝试置反enemyA和enemyB的前进方向*/

    bool try_player_contact_with_enemy(MagiciteGameMoveAbleLiving* player, MagiciteGameLiving* enemy);
    /*判断player和enemy碰撞 如果player在enemy上方 则杀死enemy 让player重新跳跃 否则游戏结束*/

    bool try_player_to_end(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    /*判断player走到结束点*/

    bool try_player_to_pitfall(MagiciteGameObject* objectA, MagiciteGameObject* objectB);
    /*判断player遇到陷阱*/

    bool try_friend_to_enemy(MagiciteGameLiving* livingA, MagiciteGameLiving* livingB);
    /*判断friend和enemy的碰撞*/

    bool try_friend_to_pitfall(MagiciteGameObject* objectA, MagiciteGameObject* objectB);

}

#endif //__MAGICITE_GAME_CONTACT__