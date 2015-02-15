#include "MagiciteGaemFactoryMethod.h"

USING_NS_CC;

MagiciteGameLiving* MagiciteGaemFactoryMethod::createEnemy(LivingType type, bool is_to_left/* = false*/)
{
    MagiciteGameLiving* ptr = nullptr;
    switch (type)
    {
    case MagiciteGaemFactoryMethod::Piranha:
        ptr = MagiciteGamePiranha::create();
        if (ptr != nullptr)
        {
            return ptr;
        }
        break;
    case MagiciteGaemFactoryMethod::Human:
        ptr = MagiciteGameHuman::create();
        if (ptr != nullptr)
        {
            auto human = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            human->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGaemFactoryMethod::Chicken:
        ptr = MagiciteGameChicken::create();
        if (ptr != nullptr)
        {
            auto chicken = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            chicken->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGaemFactoryMethod::Slime:
        ptr = MagiciteGameSlime::create();
        if (ptr != nullptr)
        {
            auto slime = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            slime->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGaemFactoryMethod::Sheep:
        ptr = MagiciteGameSheep::create();
        if (ptr != nullptr)
        {
            auto Sheep = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            Sheep->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    default:
        break;
    }
    return nullptr;
}

void MagiciteGaemFactoryMethod::destroyEnemy(MagiciteGameLiving* living)
{
    living->Dead();
}

MagiciteGameMoveAbleLiving* MagiciteGaemFactoryMethod::createFriend(LivingType type, bool is_to_left/* = false*/)
{
    MagiciteGameMoveAbleLiving* ptr = nullptr;
    switch (type)
    {
    case MagiciteGaemFactoryMethod::Human:
        ptr = MagiciteGameHuman::create();
        if (ptr != nullptr)
        {
            ptr->_is_friend = true;
            auto human = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            human->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGaemFactoryMethod::Chicken:
        ptr = MagiciteGameChicken::create();
        if (ptr != nullptr)
        {
            ptr->_is_friend = true;
            auto human = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            human->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGaemFactoryMethod::Slime:
        ptr = MagiciteGameSlime::create();
        if (ptr != nullptr)
        {
            ptr->_is_friend = true;
            auto slime = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            slime->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGaemFactoryMethod::Sheep:
        ptr = MagiciteGameSheep::create();
        if (ptr != nullptr)
        {
            ptr->_is_friend = true;
            auto slime = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            slime->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    default:
        break;
    }
    return nullptr;
}

void MagiciteGaemFactoryMethod::destroyFriend(MagiciteGameMoveAbleLiving* living)
{
    living->Dead();
}

MagiciteGamePitfall* MagiciteGaemFactoryMethod::createPitfall(Pitfall_Type type, bool is_active /*= true*/)
{
    MagiciteGamePitfall* ptr = nullptr;
    switch (type)
    {
    case MagiciteGaemFactoryMethod::Spine_Type:
        ptr = MagiciteGameSpinePitfall::create();
        if (ptr != nullptr)
        {
            ptr->setPitFallAvtive(is_active);
        }
        return ptr;
    case MagiciteGaemFactoryMethod::Pitfall:
        ptr = MagiciteGamePitfall::create();
        if (ptr != nullptr)
        {
            ptr->setPitFallAvtive(is_active);
        }
        return ptr;
    default:
        break;
    }
    return nullptr;
}

void MagiciteGaemFactoryMethod::destroyPitfall(MagiciteGamePitfall* ptr)
{
    ptr->Dead();
}

MagiciteGameAmmo* MagiciteGaemFactoryMethod::createAmmo(AmmoType type)
{
    MagiciteGameAmmo* ammo = nullptr;
    switch (type)
    {
    case MagiciteGaemFactoryMethod::FireBall:
        ammo = MagiciteGameFireball::create();
        break;
    case MagiciteGaemFactoryMethod::Acid:
        ammo = MagiciteGameAcid::create();
        break;
    default:
        break;
    }

    return ammo;
}