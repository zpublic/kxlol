#include "MagiciteGameEnemyManager.h"

USING_NS_CC;

MagiciteGameEnemyManager::MagiciteGameEnemyManager()
{
    
}

MagiciteGameEnemyManager::~MagiciteGameEnemyManager()
{

}

MagiciteGameEnemy* MagiciteGameEnemyManager::createEnemy(EnemyType type, Vec2 pos)
{
    MagiciteGameEnemy* enemy = nullptr;
    switch (type)
    {
    case MagiciteGameEnemyManager::Chicken_Type:
        enemy = MagiciteGameEnemyChicken::create();
        enemy->setPosition(pos);
        _enemys.push_back(enemy);
        return enemy;
        break;
    default:
        break;
    }
    return nullptr;
}

void MagiciteGameEnemyManager::destroyEnemy(MagiciteGameEnemy* ptr)
{
    if (ptr != nullptr)
    {
        auto enemyIter = std::find(_enemys.begin(), _enemys.end(), ptr);
        if (enemyIter != _enemys.end())
        {
            _enemys.erase(enemyIter);
            ptr->Dead();
        }
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

MagiciteGameEnemy* MagiciteGameEnemyManager::createEnemy(EnemyType type, Vec2 pos, bool is_move_to_right)
{
    auto enemy = createEnemy(type, pos);
    if (enemy != nullptr)
    {
        enemy->setMoveDire(is_move_to_right ?
            MagiciteGameLiving::Direction::right :
            MagiciteGameLiving::Direction::left);
    }
    return enemy;
}
