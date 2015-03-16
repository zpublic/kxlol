#ifndef __MAGICITE_GAME_GROUND__
#define __MAGICITE_GAME_GROUND__

#include "MagiciteGameObject.h"

class MagiciteGameGround : public MagiciteGameObject
{
public:
    MagiciteGameGround();
    ~MagiciteGameGround();

    virtual bool init();
    virtual bool initWithFile(const char* filename);

    virtual void onStep();

    CREATE_FUNC(MagiciteGameGround);
};

#endif //__MAGICITE_GAME_GROUND__
