#include "AequitasLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

bool AequitasLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    this->setKeyboardEnabled(true);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    auto act = MoveTo::create(1.0f, Vec2(250, 200));
    sprite->runAction(act);
    this->addChild(sprite, 0);

    const char* p[12] =
    {
        "1!",
        "1#",
        "2!",
        "2#",
        "3!",
        "4!",
        "4#",
        "5!",
        "5#",
        "6!",
        "6#",
        "7!",
    };
    char sPath[30] = {0};
    for (auto i = 1; i < 8; ++i)
    {
        for (auto j = 0; j < 12; ++j)
        {
            sprintf_s(sPath, "piano/%d%s.wav", i, p[j]);
            SimpleAudioEngine::getInstance()->preloadEffect(sPath);
        }
    }

    return true;
}

void AequitasLayer::onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event )
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_0:
        SimpleAudioEngine::getInstance()->playEffect("piano/35!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_1:
        SimpleAudioEngine::getInstance()->playEffect("piano/41!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_2:
        SimpleAudioEngine::getInstance()->playEffect("piano/42!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_3:
        SimpleAudioEngine::getInstance()->playEffect("piano/43!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_4:
        SimpleAudioEngine::getInstance()->playEffect("piano/44!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_5:
        SimpleAudioEngine::getInstance()->playEffect("piano/45!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_6:
        SimpleAudioEngine::getInstance()->playEffect("piano/46!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_7:
        SimpleAudioEngine::getInstance()->playEffect("piano/47!.wav");
        break;
    default:
        break;
    }
}
