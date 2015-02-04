#ifndef __MAGICITE_GAME_PITFALL_MANAGER__
#define __MAGICITE_GAME_PITFALL_MANAGER__

#include "cocos2d.h"
#include "MagiciteGamePitfallClamp.h"
#include "MagiciteGamePhyLayer.h"

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
    MagiciteGamePitfall* createPitfall(
        PitfallType type, 
        cocos2d::Vec2 pos, 
        MagiciteGamePhyLayer* phylayer, 
        bool is_turn_on = true);

    void destoryPitfall(MagiciteGamePitfall* pitfall);

protected:
    MagiciteGamePitfall* create_and_push(PitfallType type, cocos2d::Vec2 pos);
private:
    std::vector<MagiciteGamePitfall*>                   _pitfalls;
};

#endif //__MAGICITE_GAME_PITFALL_MANAGER__