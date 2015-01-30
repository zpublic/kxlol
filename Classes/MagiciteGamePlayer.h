#ifndef __MAGICITE_GAME_PLAYER__
#define __MAGICITE_GAME_PLAYER__

#include "cocos2d.h"
#include "MagiciteGameLiving.h"

class MagiciteGamePlayer : public MagiciteGameLiving
{
public:
    MagiciteGamePlayer();
    ~MagiciteGamePlayer();

    virtual bool initWithFile(const char* filename);
    static MagiciteGamePlayer* create(const char* filename);

};

#endif //__MAGICITE_GAME_PLAYER__

