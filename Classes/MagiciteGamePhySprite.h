#ifndef __MAGICITE_GAME_PHY_SPRITE__
#define __MAGICITE_GAME_PHY_SPRITE__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

class MagiciteGamePhySprite : public cocos2d::Sprite
{
public:
    MagiciteGamePhySprite();
    ~MagiciteGamePhySprite();

    b2Body* getBody() const;
    void setBody(b2Body*);

    bool isDead();
    void Dead();

    virtual bool initWithFile(const char* filename);

    CREATE_FUNC(MagiciteGamePhySprite);
    static MagiciteGamePhySprite* create(const char* filename);

    enum SpriteType : int
    {
        T_Living,
        T_Ground,
        T_End,
        T_Pitfall,
    };
    SpriteType              _SpriteType;

protected:
    b2Body*                 _body;
    bool                    _is_dead;
};

#endif //__MAGICITE_GAME_PHY_SPRITE__