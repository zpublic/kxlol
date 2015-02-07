#include "MagiciteGameEnemyManager.h"


MagiciteGameEnemyManager::MagiciteGameEnemyManager()
{

}

MagiciteGameLiving* MagiciteGameEnemyManager::createEnemy(LivingType type, bool is_to_left/* = false*/)
{
    MagiciteGameLiving* ptr = nullptr;
    switch (type)
    {
    case MagiciteGameEnemyManager::Piranha:
        ptr = MagiciteGamePiranha::create();
        if (ptr != nullptr)
        {
            _static_enemys.push_back(ptr);
            return ptr;
        }
        break;
    case MagiciteGameEnemyManager::Human:
        ptr = MagiciteGameHuman::create();
        if (ptr != nullptr)
        {
            _dynamic_enemys.push_back(ptr);
            auto human = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            human->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
            return ptr;
        }
        break;
    case MagiciteGameEnemyManager::Chicken:
        ptr = MagiciteGameChicken::create();
        if (ptr != nullptr)
        {
            _dynamic_enemys.push_back(ptr);
            auto chicken = reinterpret_cast<MagiciteGameMoveAbleLiving*>(ptr);
            chicken->setDire(is_to_left ? MagiciteGameMoveAbleLiving::Direction::left : MagiciteGameMoveAbleLiving::Direction::right);
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
    if (living->LivingMoveType != MagiciteGameLiving::MoveAbleLiving)
    {
        auto iter = std::find(_static_enemys.begin(), _static_enemys.end(), living);
        if (iter != _static_enemys.end())
        {
            (*iter)->Dead();
            _static_enemys.erase(iter);
        }
    }
    else
    {
        auto iter = std::find(_dynamic_enemys.begin(), _dynamic_enemys.end(), living);
        if (iter != _dynamic_enemys.end())
        {
            (*iter)->Dead();
            _dynamic_enemys.erase(iter);
        }
    }
}

void MagiciteGameEnemyManager::updateEnemyPos()
{
    for (auto Ptr : _dynamic_enemys)
    {
        auto enemyPtr = reinterpret_cast<MagiciteGameMoveAbleLiving*>(Ptr);
        if (enemyPtr->getDire() == MagiciteGameMoveAbleLiving::Direction::left)
        {
            enemyPtr->Move(MagiciteGameMoveAble::left);
        }
        else
        {
            enemyPtr->Move(MagiciteGameMoveAble::right);
        }
    }
}