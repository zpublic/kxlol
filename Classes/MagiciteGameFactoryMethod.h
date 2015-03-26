#ifndef __MAGICITE_GAME_FACTORY_METHOD__
#define __MAGICITE_GAME_FACTORY_METHOD__

class MagiciteGameLiving;
class MagiciteGameMoveAbleLiving;
class MagiciteGamePitfall;
class MagiciteGameAmmo;
class MagiciteGameGround;

namespace MagiciteGameFactoryMethod
{
    enum Pitfall_Type : int
    {
        Piranha,
        Pitfall,
        Spine_Type,
        Meteorite,
    };
    enum LivingType
    {
        Human,
        Chicken,
        Slime,
        Sheep,
        Dirt,
        NPC,
    };

    enum AmmoType : int
    {
        FireBall,
        Acid,
    };

    enum GroundType : int
    {
        Ground,
        FragileGround,
        MoveAbleGround,
    };

    MagiciteGameLiving* createLiving(LivingType type);
    MagiciteGameMoveAbleLiving* createFriend(LivingType type);
    MagiciteGameMoveAbleLiving* createEnemy(LivingType type);
    MagiciteGamePitfall* createPitfall(Pitfall_Type type);
    MagiciteGameAmmo* createAmmo(AmmoType type);
    MagiciteGameGround* createGround(GroundType type);
        
    void destroyEnemy(MagiciteGameLiving* living);
    void destroyFriend(MagiciteGameLiving* living);
    void destroyLiving(MagiciteGameLiving* living);
    void destroyPitfall(MagiciteGamePitfall* pitfall);

};

#endif //__MAGICITE_GAME_FACTORY_METHOD__