#ifndef __MAGICITE_GAME_PHY_SPRITE__
#define __MAGICITE_GAME_PHY_SPRITE__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

class MagiciteGamePhySprite : public cocos2d::Sprite
{
public:
    b2Body* getBody() const;
    void setBody(b2Body*);

    CREATE_FUNC(MagiciteGamePhySprite);
    static MagiciteGamePhySprite* create(const char* filename);

private:
    b2Body*                 _body;
};

#endif //__MAGICITE_GAME_PHY_SPRITE__