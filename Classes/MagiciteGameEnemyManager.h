#ifndef __MAGICITE_GAME_ENEMY_MANAGER__
#define __MAGICITE_GAME_ENEMY_MANAGER__

#include "MagiciteGameEnemy.h"

class MagiciteGameEnemyManager
{

public:
    static MagiciteGameEnemyManager* getInstance();

    MagiciteGameEnemy* createEnemy(cocos2d::Vec2 pos);

private:
    static MagiciteGameEnemyManager*            _instance;

    MagiciteGameEnemyManager();
    ~MagiciteGameEnemyManager();
};

#endif //__MAGICITE_GAME_ENEMY_MANAGER__