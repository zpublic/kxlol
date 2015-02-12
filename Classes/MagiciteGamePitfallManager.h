#ifndef __MAGICITE__GAME_PITFALL_MANAGER__
#define __MAGICITE__GAME_PITFALL_MANAGER__

#include "vector"
#include "MagiciteGameSpinePitfall.h"


namespace MagiciteGamePitfallManager
{
    enum Pitfall_Type : int
    {
        Spine_Type,
    };

    MagiciteGamePitfall* createPitfall(Pitfall_Type type, bool is_active = true);
    void destroyPitfall(MagiciteGamePitfall* ptr);
};

#endif //__MAGICITE__GAME_PITFALL_MANAGER__