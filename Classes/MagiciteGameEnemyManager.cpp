#include "MagiciteGameEnemyManager.h"

MagiciteGameEnemyManager* MagiciteGameEnemyManager::_instance = nullptr;

USING_NS_CC;


MagiciteGameEnemyManager::MagiciteGameEnemyManager()
{

}


MagiciteGameEnemyManager::~MagiciteGameEnemyManager()
{

}

MagiciteGameEnemyManager* MagiciteGameEnemyManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new MagiciteGameEnemyManager();
    }
    return _instance;
}

MagiciteGameEnemy* MagiciteGameEnemyManager::createEnemy(Vec2 pos)
{
    auto enemy = MagiciteGameEnemy::create("CloseNormal.png");
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
        if (enemyPtr->getPositionX() != enemyPtr->_end_x_pos)
        {
            if (enemyPtr->getPositionX() < enemyPtr->_end_x_pos)
            {
                if (enemyPtr->getPositionX() < enemyPtr->_end_x_pos - enemyPtr->_speed)
                {
                    enemyPtr->Move(MagiciteGameLiving::Direction::right);
                }
                else
                {
                    enemyPtr->Move(MagiciteGameLiving::Direction::right);
                    b2Vec2 pos = b2Vec2(enemyPtr->_end_x_pos / PTM_RATIO, enemyPtr->getPositionY() / PTM_RATIO);
                    float angle = -1 * CC_RADIANS_TO_DEGREES(enemyPtr->getBody()->GetAngle());
                    enemyPtr->getBody()->SetTransform(pos, angle);
                    enemyPtr->Stop();
                }
            }
            else
            {
                if (enemyPtr->_end_x_pos < enemyPtr->getPositionX() - enemyPtr->_speed)
                {
                    enemyPtr->Move(MagiciteGameLiving::Direction::left);
                }
                else
                {
                    enemyPtr->Move(MagiciteGameLiving::Direction::left);
                    b2Vec2 pos = b2Vec2(enemyPtr->_end_x_pos / PTM_RATIO, enemyPtr->getPositionY() / PTM_RATIO);
                    float angle = -1 * CC_RADIANS_TO_DEGREES(enemyPtr->getBody()->GetAngle());
                    enemyPtr->getBody()->SetTransform(pos, angle);
                    enemyPtr->Stop();
                }
            }
        }
    }
    
}

MagiciteGameEnemy* MagiciteGameEnemyManager::createEnemy(cocos2d::Vec2 pos, float move_to)
{
    auto enemy = MagiciteGameEnemy::create("CloseNormal.png");
    if (enemy != nullptr)
    {
        enemy->setPosition(pos);
        enemy->setMoveTo(move_to);
        _enemys.push_back(enemy);
        return enemy;
    }
    return nullptr;
}