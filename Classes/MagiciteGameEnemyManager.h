#ifndef __MAGICITE_GAME_ENEMY_MANAGER__
#define __MAGICITE_GAME_ENEMY_MANAGER__

#include "vector"
#include "MagiciteGameLiving.h"
#include "MagiciteGameHuman.h"
#include "MagiciteGameChicken.h"
#include "MagiciteGamePiranha.h"
#include "MagiciteGameSlime.h"
#include "MagiciteGameSheep.h"

class MagiciteGameEnemyManager
{
public:
    MagiciteGameEnemyManager();
    
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

    void updateEnemyPos();

private:
    std::vector<MagiciteGameLiving*> _dynamic_enemys;
    std::vector<MagiciteGameLiving*> _static_enemys;
};

#endif //__MAGICITE_GAME_ENEMY_MANAGER__