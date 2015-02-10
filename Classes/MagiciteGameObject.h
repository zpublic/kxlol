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

    enum _entityCategory : uint16
    {
        DEFAULT_GROUND   = 0x0001,
        DEFAULT_LIVING   = 0x0002,
        DEFAULT_ENEMY    = 0x0004,
        DEFAULT_PITFALL  = 0x0008,
        DEFAULT_END      = 0x0010,
        DEFAULT_FRIEND   = 0x0020,
        DEFAULT_AMMO     = 0x0040,
        DEFAULT_ALL      = 0xFFFF,
    };

    MagiciteGameObject(Type type = T_Ground);

    virtual bool init();
    virtual bool initWithFile(const char* filename);

    CREATE_FUNC(MagiciteGameObject);
    static MagiciteGameObject* create(Type type);
    static MagiciteGameObject* create(const char* filename);
};

#endif //__MAGICITE_GAME_OBJECT__