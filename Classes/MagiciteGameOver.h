#ifndef __MAGICITE_GAME_OVER__
#define __MAGICITE_GAME_OVER__

#include "cocos2d.h"
#include "MagiciteScene.h"
#include "WelcomeScene.h"

class MagiciteGameOver : public cocos2d::Scene
{
public:
    MagiciteGameOver();
    ~MagiciteGameOver();

    virtual bool init();
    static MagiciteGameOver* create(cocos2d::RenderTexture *tex);
    static void Over(cocos2d::Layer* ptr);
};

#endif //__MAGICITE_GAME_OVER__