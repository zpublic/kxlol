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
        return enemy;
    }
    return nullptr;
}
