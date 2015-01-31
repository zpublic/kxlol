#ifndef __MAGICITE_GAME_ENEMY__
#define __MAGICITE_GAME_ENEMY__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "MagiciteGameLiving.h"

class MagiciteGameEnemyManager;

class MagiciteGameEnemy : public MagiciteGameLiving
{
    friend class MagiciteGameEnemyManager;
public:
    MagiciteGameEnemy();
    ~MagiciteGameEnemy();

    void setMoveTo(float new_x_pos);

    virtual bool initWithFile(const char* filename);
    static MagiciteGameEnemy* create(const char* filename);

private:
    float                       _start_x_pos;
    float                       _end_x_pos;
};

#endif //__MAGICITE_GAME_ENEMY__