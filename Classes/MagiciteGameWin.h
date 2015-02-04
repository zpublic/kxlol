#ifndef __MAGICITE_GAME_WIN__
#define __MAGICITE_GAME_WIN__

#include "cocos2d.h"
#include "WelcomeScene.h"

class MagiciteGameWin : public cocos2d::Scene
{
public:
    MagiciteGameWin();
    ~MagiciteGameWin();

    virtual bool init();
    static MagiciteGameWin* create(cocos2d::RenderTexture *tex);
    static void Win(cocos2d::Layer* ptr);
};

#endif //__MAGICITE_GAME_WIN__