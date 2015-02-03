#ifndef __MAGICITE_GAME_ENEMY_MANAGER__
#define __MAGICITE_GAME_ENEMY_MANAGER__

#include "MagiciteGameEnemy.h"
#include "MagiciteGameEnemyChicken.h"
#include "vector"

class MagiciteGameEnemyManager
{

public:
    MagiciteGameEnemyManager();
    ~MagiciteGameEnemyManager();

    static const int PTM_RATIO = 32;

    enum EnemyType : int
    {
        Unknow_Type,
        Chicken_Type,
    };

    MagiciteGameEnemy* createEnemy(EnemyType type, cocos2d::Vec2 pos);
    MagiciteGameEnemy* createEnemy(EnemyType type, cocos2d::Vec2 pos, bool is_move_to_right);
    void destroyEnemy(MagiciteGameEnemy* ptr);

    void updateEnemyPosition();

private:
    std::vector<MagiciteGameEnemy*>             _enemys;
};

#endif //__MAGICITE_GAME_ENEMY_MANAGER__