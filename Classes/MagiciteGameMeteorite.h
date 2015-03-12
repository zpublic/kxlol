#ifndef __MAGICITE_GAME_METEORITE__
#define __MAGICITE_GAME_METEORITE__

#include "MagiciteGameMovePitfall.h"

class MagiciteGameMeteorite : public MagiciteGameMovePitfall
{
public:
    MagiciteGameMeteorite();
    ~MagiciteGameMeteorite();

    virtual bool init();

    CREATE_FUNC(MagiciteGameMeteorite);
};

#endif //__MAGICITE_GAME_METEORITE__