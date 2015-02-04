#ifndef __MAGICITE_GAME_PITFALL_CLAMP__
#define __MAGICITE_GAME_PITFALL_CLAMP__

#include "cocos2d.h"
#include "MagiciteGamePitfall.h"

class MagiciteGamePitfallClamp : public MagiciteGamePitfall
{
public:
    MagiciteGamePitfallClamp();
    ~MagiciteGamePitfallClamp();

    virtual bool init();
    static MagiciteGamePitfallClamp* create();

};

#endif //__MAGICITE_GAME_PITFALL_CLAMP__