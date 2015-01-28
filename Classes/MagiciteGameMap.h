#ifndef __MAGICITE_GAME_MAP__
#define __MAGICITE_GAME_MAP__

#include "cocos2d.h"

class MagiciteGameMap : public cocos2d::Layer
{
public:
    MagiciteGameMap();
    ~MagiciteGameMap();

    virtual bool init(cocos2d::TMXTiledMap* map);
    cocos2d::Size getBackSize() const;

    static MagiciteGameMap* create(cocos2d::TMXTiledMap *map);

private:
    cocos2d::Size           _visibleSize;
    cocos2d::TMXTiledMap*   _BackGround;
};

#endif