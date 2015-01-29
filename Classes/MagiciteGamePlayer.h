#ifndef __MAGICITE_GAME_PLAYER__
#define __MAGICITE_GAME_PLAYER__

#include "cocos2d.h"
#include "MagiciteGameLivine.h"

class MagiciteGamePlayer : public MagiciteGameLivine
{
public:
    MagiciteGamePlayer();
    ~MagiciteGamePlayer();

    virtual bool initWithFile(const char* filename);
    static MagiciteGamePlayer* create(const char* filename);

};

#endif //__MAGICITE_GAME_PLAYER__

