#include "MagiciteGameEnemyManager.h"

USING_NS_CC;

MagiciteGameEnemyManager::MagiciteGameEnemyManager()
{

}

MagiciteGameEnemyManager::~MagiciteGameEnemyManager()
{

}

MagiciteGameEnemy* MagiciteGameEnemyManager::createEnemy(Vec2 pos)
{
    auto enemy = MagiciteGameEnemy::create("img\\Magicite\\enemy\\chicken_stop.png");
    if (enemy != nullptr)
    {
        enemy->setPosition(pos);
        _enemys.push_back(enemy);
        return enemy;
    }
    return nullptr;
}

void MagiciteGameEnemyManager::destroyEnemy(MagiciteGameEnemy* ptr)
{
    if (ptr != nullptr)
    {
        _enemys.erase(std::find(_enemys.begin(), _enemys.end(), ptr));
        ptr->Dead();
    }
}

void MagiciteGameEnemyManager::updateEnemyPosition()
{
    for (auto enemyPtr : _enemys)
    {
        if (enemyPtr->_Move_To_Dire == MagiciteGameLiving::Direction::right)
        {
            enemyPtr->Move(MagiciteGameLiving::Direction::right);
        }
        else if (enemyPtr->_Move_To_Dire == MagiciteGameLiving::Direction::left)
        {
            enemyPtr->Move(MagiciteGameLiving::Direction::left);
        }
    }
}

MagiciteGameEnemy* MagiciteGameEnemyManager::createEnemy(Vec2 pos, bool is_move_to_right)
{
    auto enemy = MagiciteGameEnemy::create("img\\Magicite\\enemy\\chicken_stop.png");
    if (enemy != nullptr)
    {
        enemy->setPosition(pos);
        enemy->setMoveDire(is_move_to_right ? 
            MagiciteGameLiving::Direction::right: 
            MagiciteGameLiving::Direction::left);
        _enemys.push_back(enemy);
        return enemy;
    }
    return nullptr;
}
