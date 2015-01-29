#ifndef __MAGICITE_GAME_ENEMY__
#define __MAGICITE_GAME_ENEMY__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "MagiciteGameLivine.h"

class MagiciteGameEnemy : public MagiciteGameLivine
{
public:
    MagiciteGameEnemy();
    ~MagiciteGameEnemy();

    virtual bool initWithFile(const char* filename);
    static MagiciteGameEnemy* create(const char* filename);
};

#endif //__MAGICITE_GAME_ENEMY__