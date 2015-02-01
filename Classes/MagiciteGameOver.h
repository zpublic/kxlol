#ifndef __MAGICITE_GAME_OVER__
#define __MAGICITE_GAME_OVER__

#include "cocos2d.h"
#include "MagiciteScene.h"
#include "WelcomeScene.h"

class MagiciteGameOver : public cocos2d::Layer
{
public:
    MagiciteGameOver();
    ~MagiciteGameOver();

    virtual bool init();
    static cocos2d::Scene* createScene(cocos2d::RenderTexture *tex);
    static void Over(cocos2d::Layer* ptr);

    CREATE_FUNC(MagiciteGameOver);
};

#endif //__MAGICITE_GAME_OVER__