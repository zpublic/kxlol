#ifndef __MAGICITE_GAME_PITFALL_CLAMP__
#define __MAGICITE_GAME_PITFALL_CLAMP__

#include "cocos2d.h"
#include "MagiciteGamePitfall.h"

class MagiciteGamePitfallClamp : public MagiciteGamePitfall
{
public:
    MagiciteGamePitfallClamp();
    ~MagiciteGamePitfallClamp();

    virtual bool init(bool is_turn_on);
    static MagiciteGamePitfallClamp* create(bool is_turn_on);

};

#endif //__MAGICITE_GAME_PITFALL_CLAMP__