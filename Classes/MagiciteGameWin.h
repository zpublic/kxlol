#ifndef __MAGICITE_GAME_WIN__
#define __MAGICITE_GAME_WIN__

#include "cocos2d.h"
#include "WelcomeScene.h"

class MagiciteGameWin : public cocos2d::Layer
{
public:
    MagiciteGameWin();
    ~MagiciteGameWin();

    virtual bool init();
    static cocos2d::Scene* createScene(cocos2d::RenderTexture *tex);
    static void Win(cocos2d::Layer* ptr);

    CREATE_FUNC(MagiciteGameWin);
};

#endif //__MAGICITE_GAME_WIN__