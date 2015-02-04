#ifndef __MAGICITE_GAME_FUNC__
#define __MAGICITE_GAME_FUNC__

#include "cocos2d.h"
#include "MagiciteGameEnemy.h"
#include "MagiciteGamePlayer.h"
#include "MagiciteGameLiving.h"

namespace MagiciteGameFunc
{
    bool is_player_to_end(MagiciteGamePhySprite* spriteA, MagiciteGamePhySprite* spriteB);
    bool is_sprite_type_same(MagiciteGamePhySprite* spriteA, MagiciteGamePhySprite* spriteB);
    bool is_has_living(MagiciteGamePhySprite* spriteA, MagiciteGamePhySprite* spriteB);
    bool is_living_type_same(MagiciteGameLiving *livingA, MagiciteGameLiving* livingB);
    bool is_player_and_enemy(MagiciteGameLiving* livingA, MagiciteGameLiving* livingB);
    void changeEnemyDirection(MagiciteGameEnemy* enemy);
    bool is_player_above_enemy(MagiciteGamePlayer* player, MagiciteGameEnemy* enemy);
    bool is_living_above_ground(MagiciteGameLiving* living, MagiciteGamePhySprite* ground);
    bool is_enemy_on_ground(MagiciteGameEnemy* enemy, MagiciteGamePhySprite* ground);
    bool is_enemy_above_ground(MagiciteGameEnemy* enemy, MagiciteGamePhySprite* ground);

    MagiciteGamePlayer* trivialPlayer(MagiciteGameLiving* livingA, MagiciteGameLiving* livingB);
    MagiciteGameEnemy* trivialEnemy(MagiciteGameLiving* livingA, MagiciteGameLiving* livingB);
    MagiciteGameLiving* trivialLiving(MagiciteGamePhySprite* spriteA, MagiciteGamePhySprite* spriteB);
    MagiciteGamePhySprite* trivialGround(MagiciteGamePhySprite* spriteA, MagiciteGamePhySprite* spriteB);
};

#endif 