#include "MagiciteGameFactoryMethod.h"
#include "MagiciteGamePitfall.h"
#include "MagiciteGameLiving.h"
#include "MagiciteGameAmmo.h"
#include "MagiciteGameHuman.h"
#include "MagiciteGameChicken.h"
#include "MagiciteGamePiranha.h"
#include "MagiciteGameSlime.h"
#include "MagiciteGameSheep.h"
#include "MagiciteGameSpinePitfall.h"
#include "MagiciteGameFireball.h"
#include "MagiciteGameAcid.h"
#include "MagiciteGameDirt.h"
#include "MagiciteGameNPC.h"
#include "MagiciteGameGround.h"
#include "MagiciteGameFragileGround.h"
#include "MagiciteGameMoveAbleGround.h"
#include "MagiciteGameMeteorite.h"

USING_NS_CC;

MagiciteGameMoveAbleLiving* MagiciteGameFactoryMethod::createEnemy(LivingType type)
{
    auto ptr = reinterpret_cast<MagiciteGameMoveAbleLiving*>(createLiving(type));
    return ptr;
}

MagiciteGameMoveAbleLiving* MagiciteGameFactoryMethod::createFriend(LivingType type)
{
    auto ptr = reinterpret_cast<MagiciteGameMoveAbleLiving*>(createLiving(type));
    if (ptr)
    {
        auto enemy = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
        enemy->_is_friend = true;
        return enemy;
    }
    return nullptr;
}

MagiciteGamePitfall* MagiciteGameFactoryMethod::createPitfall(Pitfall_Type type)
{
    MagiciteGamePitfall* ptr = nullptr;
    switch (type)
    {
    case MagiciteGameFactoryMethod::Piranha:
        ptr = MagiciteGamePiranha::create();
        break;
    case MagiciteGameFactoryMethod::Pitfall:
        ptr = MagiciteGamePitfall::create();
        break;
    case MagiciteGameFactoryMethod::Spine_Type:
        ptr = MagiciteGameSpinePitfall::create();
        break;
    case MagiciteGameFactoryMethod::Meteorite:
        break;
        ptr = MagiciteGameMeteorite::create();
    default:
        break;
    }
    
    if (ptr)
    {
        ptr->setPitFallAvtive(true);
    }
    return ptr;
}

MagiciteGameAmmo* MagiciteGameFactoryMethod::createAmmo(AmmoType type)
{
    MagiciteGameAmmo* ammo = nullptr;
    switch (type)
    {
    case MagiciteGameFactoryMethod::FireBall:
        ammo = MagiciteGameFireball::create();
        break;
    case MagiciteGameFactoryMethod::Acid:
        ammo = MagiciteGameAcid::create();
        break;

    default:
        break;
    }

    return ammo;
}

MagiciteGameLiving* MagiciteGameFactoryMethod::createLiving(LivingType type)
{
    MagiciteGameLiving* ptr = nullptr;
    switch (type)
    {
    case MagiciteGameFactoryMethod::Human:
        ptr = MagiciteGameHuman::create();
        break;
    case MagiciteGameFactoryMethod::Chicken:
        ptr = MagiciteGameChicken::create();
        break;
    case MagiciteGameFactoryMethod::Slime:
        ptr = MagiciteGameSlime::create();
        break;
    case MagiciteGameFactoryMethod::Sheep:
        ptr = MagiciteGameSheep::create();
        break;
    case MagiciteGameFactoryMethod::Dirt:
        ptr = MagiciteGameDirt::create();
        break;
    case MagiciteGameFactoryMethod::NPC:
        ptr = MagiciteGameNPC::create();
        break;
    default:
        break;
    }
    return ptr;
}

MagiciteGameGround* MagiciteGameFactoryMethod::createGround(GroundType type)
{
    MagiciteGameGround* ground = nullptr;
    switch (type)
    {
    case MagiciteGameFactoryMethod::Ground:
        ground = MagiciteGameGround::create();
        break;
    case MagiciteGameFactoryMethod::FragileGround:
        ground = MagiciteGameFragileGround::create();
        break;
    case MagiciteGameFactoryMethod::MoveAbleGround:
        ground = MagiciteGameMoveAbleGround::create();
        break;
    default:
        break;
    }
    return ground;
}

void MagiciteGameFactoryMethod::destroyEnemy(MagiciteGameLiving* living)
{
    destroyLiving(living);
}

void MagiciteGameFactoryMethod::destroyFriend(MagiciteGameLiving* living)
{
    destroyLiving(living);
}

void MagiciteGameFactoryMethod::destroyLiving(MagiciteGameLiving* living)
{
    living->Dead();
}

void MagiciteGameFactoryMethod::destroyPitfall(MagiciteGamePitfall* pitfall)
{
    pitfall->Dead();
}
