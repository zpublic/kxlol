#ifndef __MAGICITE_GAME_MAP__
#define __MAGICITE_GAME_MAP__

#include "cocos2d.h"

class MagiciteGameMap : public cocos2d::Layer
{
public:
    MagiciteGameMap();
    ~MagiciteGameMap();

    void MoveMap(int seed);
    bool is_left_open() const;
    bool is_right_open() const;
    virtual bool init();

    CREATE_FUNC(MagiciteGameMap);

private:
    cocos2d::Size           _visibleSize;
    cocos2d::Sprite*        _BackGround;
    bool                    _left_open;
    bool                    _right_open;
};

#endif