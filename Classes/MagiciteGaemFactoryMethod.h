#ifndef __MAGICITE_GAME_FACTORY_METHOD__
#define __MAGICITE_GAME_FACTORY_METHOD__

#include "MagiciteGameLiving.h"
#include "MagiciteGameHuman.h"
#include "MagiciteGameChicken.h"
#include "MagiciteGamePiranha.h"
#include "MagiciteGameSlime.h"
#include "MagiciteGameSheep.h"
#include "MagiciteGameSpinePitfall.h"
#include "MagiciteGameFireball.h"
#include "MagiciteGameAcid.h"
#include "MagiciteGameDirt.h"

namespace MagiciteGaemFactoryMethod
{
    enum Pitfall_Type : int
    {
        Pitfall,
        Spine_Type,
    };
    enum LivingType
    {
        Piranha,
        Human,
        Chicken,
        Slime,
        Sheep,
        Dirt,
    };

    enum AmmoType : int
    {
        FireBall,
        Acid,
    };

    MagiciteGameMoveAbleLiving* createFriend(LivingType type, bool is_to_left = false);
    void destroyFriend(MagiciteGameMoveAbleLiving* living);

    MagiciteGameLiving* createEnemy(LivingType type, bool is_to_left = false);
    void destroyEnemy(MagiciteGameLiving* living);

    MagiciteGamePitfall* createPitfall(Pitfall_Type type, bool is_active = true);
    void destroyPitfall(MagiciteGamePitfall* ptr);

    MagiciteGameAmmo* createAmmo(AmmoType type);

};

#endif //__MAGICITE_GAME_FACTORY_METHOD__