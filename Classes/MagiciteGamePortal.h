#ifndef __MAGICITE_GAME_PROTAL__
#define __MAGICITE_GAME_PROTAL__

#include "MagiciteGameObject.h"

class MagiciteGamePortal : public MagiciteGameObject
{
public:
    MagiciteGamePortal();
    ~MagiciteGamePortal();

    virtual bool init();
    virtual bool initWithFile(const char* filename);

    MagiciteGamePortal* getPair();
    void setPair(MagiciteGamePortal*);

    CREATE_FUNC(MagiciteGamePortal);
protected:
    MagiciteGamePortal*             _pair;
};

#endif //__MAGICITE_GAME_PROTAL__