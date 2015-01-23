#ifndef __MAIN_TAB_BTN_LAYER_H__
#define __MAIN_TAB_BTN_LAYER_H__

#include "cocos2d.h"

class MainTabBtnLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(MainTabBtnLayer);

    void TabBtnCallback(Ref* pSender);
};

#endif // __MAIN_TAB_BTN_LAYER_H__
