#ifndef __MAGICITE_GAME_MAP__
#define __MAGICITE_GAME_MAP__

#include "cocos2d.h"

class MagiciteGameMap : public cocos2d::Layer
{
public:
    MagiciteGameMap();
    ~MagiciteGameMap();

    void MoveMap(int seed);
    virtual bool init();

    CREATE_FUNC(MagiciteGameMap);

private:
    cocos2d::Size           _visibleSize;
    cocos2d::Sprite*        _BackGround;
};

#endif