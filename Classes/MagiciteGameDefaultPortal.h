#ifndef __MAGICITE_GAME_DEFAULT_PORTAL__
#define __MAGICITE_GAME_DEFAULT_PORTAL__

#include "MagiciteGamePortal.h"

class MagiciteGameDefaultPortal : public MagiciteGamePortal
{
public:
    MagiciteGameDefaultPortal();
    ~MagiciteGameDefaultPortal();

    bool init();

    CREATE_FUNC(MagiciteGameDefaultPortal);
};

#endif //__MAGICITE_GAME_DEFAULT_PORTAL__