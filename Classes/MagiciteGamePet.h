#ifndef __MAGICITE_GAME_PET__
#define __MAGICITE_GAME_PET__

#include "cocos2d.h"
#include "MagiciteGameObject.h"

class MagiciteGamePet : public MagiciteGameObject
{
public:
    MagiciteGamePet();

    virtual bool init();
    virtual bool initWithFile(const char* filename);

    CREATE_FUNC(MagiciteGamePet);
    static MagiciteGamePet* create(const char* filename);

    virtual void setFloat();
};

#endif //__MAGICITE_GAME_PET__