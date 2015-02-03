#ifndef _KXLOL_MAGICITE_BEGIN_MENU_H
#define _KXLOL_MAGICITE_BEGIN_MENU_H

#include <cocos2d.h>

class MagiciteBeginMenu : public cocos2d::Layer
{
public:
    virtual bool init();

    static cocos2d::Scene* createScene();

    CREATE_FUNC(MagiciteBeginMenu);
};

#endif