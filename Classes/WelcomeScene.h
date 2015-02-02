#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
#include "MagiciteGameSelectLevel.h"

class WelcomeScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void menuEntryCallback(cocos2d::Ref* pSender);
    void menuEntryCallback2(cocos2d::Ref* pSender);
    void menuEntryCallback3(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(WelcomeScene);
};

#endif // __WELCOME_SCENE_H__
