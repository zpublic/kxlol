#ifndef __MAGICITE_GAME_OBJECT__
#define __MAGICITE_GAME_OBJECT__

#include "cocos2d.h"
#include "MagiciteGamePhySprite.h"

class MagiciteGameObject : public MagiciteGamePhySprite
{
public:
    enum Type : int
    {
        T_Living,
        T_Ground,
        T_Pitfall,
        T_End,
        T_Ammo,
    }ObjType;

    MagiciteGameObject(Type type = T_Ground);

    virtual bool init();
    virtual bool initWithFile(const char* filename);

    CREATE_FUNC(MagiciteGameObject);
    static MagiciteGameObject* create(Type type);
    static MagiciteGameObject* create(const char* filename);
};

#endif //__MAGICITE_GAME_OBJECT__