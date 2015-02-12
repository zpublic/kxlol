#include "MagiciteGameEnemyManager.h"

MagiciteGameLiving* MagiciteGameEnemyManager::createEnemy(LivingType type, bool is_to_left/* = false*/)
{
    MagiciteGameLiving* ptr = nullptr;
    switch (type)
    {
    case MagiciteGameEnemyManager::Piranha:
        ptr = MagiciteGamePiranha::create();
        if (ptr != nullptr)
        {
            return ptr;
        }
        break;
    case MagiciteGameEnemyManager::Human:
        ptr = MagiciteGameHuman::create();
        if (ptr != nullptr)
        {
            auto human = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            human->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGameEnemyManager::Chicken:
        ptr = MagiciteGameChicken::create();
        if (ptr != nullptr)
        {
            auto chicken = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            chicken->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGameEnemyManager::Slime:
        ptr = MagiciteGameSlime::create();
        if (ptr != nullptr)
        {
            auto slime = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            slime->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGameEnemyManager::Sheep:
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

void MagiciteGameEnemyManager::destroyEnemy(MagiciteGameLiving* living)
{
    living->Dead();
}

