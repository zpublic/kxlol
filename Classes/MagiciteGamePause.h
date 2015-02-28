#ifndef __MAGICITE_GAME_PAUSE__
#define __MAGICITE_GAME_PAUSE__

#include "cocos2d.h"

class MagiciteGamePause : public cocos2d::Scene
{
public:
    MagiciteGamePause();
    ~MagiciteGamePause();

    virtual bool init();
    static MagiciteGamePause* create(cocos2d::RenderTexture *tex);
    static void Pause(cocos2d::Layer* ptr);
};

#endif //__MAGICITE_GAME_PAUSE__