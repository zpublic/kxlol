#ifndef __MAGICITE_GAME_PHY_SPRITE__
#define __MAGICITE_GAME_PHY_SPRITE__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

class MagiciteGamePhySprite : public cocos2d::Sprite
{
public:
    MagiciteGamePhySprite();
    virtual ~MagiciteGamePhySprite();

    b2Body* getBody() const;
    void setBody(b2Body*);

    bool isDead() const;
    void Dead();

    virtual bool initWithFile(const char* filename);
    virtual bool init();

    CREATE_FUNC(MagiciteGamePhySprite);
    static MagiciteGamePhySprite* create(const char* filename);

private:
    b2Body*                         _body;
    bool                            _is_dead;
};

#endif //__MAGICITE_GAME_PHY_SPRITE__