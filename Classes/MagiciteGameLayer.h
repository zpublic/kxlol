#ifndef __MAGICITE_GAME_LAYER_H__
#define __MAGICITE_GAME_LAYER_H__

#include "cocos2d.h"

class MagiciteGameLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(MagiciteGameLayer);
};

#endif // __MAGICITE_GAME_LAYER_H__
