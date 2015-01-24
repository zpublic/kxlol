#ifndef __AEQUITAS_LAYER_H__
#define __AEQUITAS_LAYER_H__

#include "cocos2d.h"

class AequitasLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    CREATE_FUNC(AequitasLayer);
};

#endif // __AEQUITAS_LAYER_H__
