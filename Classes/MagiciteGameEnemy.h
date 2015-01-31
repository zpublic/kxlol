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

    Direction getMoveDire();
    void setMoveDire(Direction move_to);
    bool getPass();

    virtual bool initWithFile(const char* filename);
    static MagiciteGameEnemy* create(const char* filename);

private:
    Direction                           _Move_To_Dire;
    bool                                _is_pass;
};

#endif //__MAGICITE_GAME_ENEMY__