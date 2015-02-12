#ifndef __MAGICITE_GAME_ENEMY_MANAGER__
#define __MAGICITE_GAME_ENEMY_MANAGER__

#include "MagiciteGameLiving.h"
#include "MagiciteGameHuman.h"
#include "MagiciteGameChicken.h"
#include "MagiciteGamePiranha.h"
#include "MagiciteGameSlime.h"
#include "MagiciteGameSheep.h"

namespace MagiciteGameEnemyManager
{
    enum LivingType
    {
        Piranha,
        Human,
        Chicken,
        Slime,
        Sheep,
    };

    MagiciteGameLiving* createEnemy(LivingType type, bool is_to_left = false);
    void destroyEnemy(MagiciteGameLiving* living);
};

#endif //__MAGICITE_GAME_ENEMY_MANAGER__