#ifndef __MAGICITE_GAME_PITFALL_MANAGER__
#define __MAGICITE_GAME_PITFALL_MANAGER__

#include "cocos2d.h"
#include "MagiciteGamePitfallClamp.h"

class MagiciteGamePitfallManager
{
public:
    MagiciteGamePitfallManager();
    ~MagiciteGamePitfallManager();

    enum PitfallType : int
    {
        Unknow_Type,
        Clamp_Type,
    };
    MagiciteGamePitfall* createPitfall(PitfallType type, cocos2d::Vec2 pos);
    MagiciteGamePitfall* createPitfall(PitfallType type, cocos2d::Vec2 pos, bool is_turn_on);
    void destoryPitfall(MagiciteGamePitfall* pitfall);

private:
    std::vector<MagiciteGamePitfall*>                   _pitfalls;
};

#endif //__MAGICITE_GAME_PITFALL_MANAGER__