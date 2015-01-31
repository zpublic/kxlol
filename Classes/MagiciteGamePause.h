#ifndef __MAGICITE_GAME_PAUSE__
#define __MAGICITE_GAME_PAUSE__

#include "cocos2d.h"
#include "MagiciteScene.h"
#include "MagiciteGameLayer.h"
#include "WelcomeScene.h"

class MagiciteGamePause : public cocos2d::Layer
{
public:
    MagiciteGamePause();
    ~MagiciteGamePause();

    virtual bool init();
    static cocos2d::Scene* createScene(cocos2d::RenderTexture *tex);
    static void Pause(cocos2d::Layer* ptr);

    CREATE_FUNC(MagiciteGamePause);
};

#endif //__MAGICITE_GAME_PAUSE__