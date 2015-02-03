#ifndef __MAGICITE_GAME_ENEMY_CHICKEN__
#define __MAGICITE_GAME_ENEMY_CHICKEN__

#include "cocos2d.h"
#include "MagiciteGameEnemy.h"

class MagiciteGameEnemyChicken : public MagiciteGameEnemy
{
public:
    MagiciteGameEnemyChicken();
    ~MagiciteGameEnemyChicken();

    virtual bool init();
    CREATE_FUNC(MagiciteGameEnemyChicken);

    virtual void initAnimation();
    virtual void startAnimation();
    virtual void stopAnimation();
};

#endif //__MAGICITE_GAME_ENEMY_CHICKEN__
