#ifndef __MAGICITE_GAME_FRAGILE_GROUND__
#define __MAGICITE_GAME_FRAGILE_GROUND__

#include "MagiciteGameGround.h"

class MagiciteGameFragileGround : public MagiciteGameGround
{
public:
    MagiciteGameFragileGround();
    ~MagiciteGameFragileGround();

    virtual bool init();
    virtual bool initWithFile(const char* filename);

    virtual void onStep();

    CREATE_FUNC(MagiciteGameFragileGround);
private:
    bool                                _is_destroy;
};

#endif //__MAGICITE_GAME_FRAGILE_GROUND__
