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

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(AequitasLayer::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(AequitasLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto sprite = Sprite::create("keyboard.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
   /* auto act = MoveTo::create(1.0f, Vec2(250, 200));
    sprite->runAction(act);*/
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

    key_map_.LoadKeyMap();

    return true;
}

void AequitasLayer::onKeyPressed( cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event )
{
    key_map_.OnKey((int)keyCode);
    return;

    switch (keyCode)
    {

    case cocos2d::EventKeyboard::KeyCode::KEY_1:
        SimpleAudioEngine::getInstance()->playEffect("piano/51!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_2:
        SimpleAudioEngine::getInstance()->playEffect("piano/52!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_3:
        SimpleAudioEngine::getInstance()->playEffect("piano/53!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_4:
        SimpleAudioEngine::getInstance()->playEffect("piano/54!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_5:
        SimpleAudioEngine::getInstance()->playEffect("piano/55!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_6:
        SimpleAudioEngine::getInstance()->playEffect("piano/56!.wav");
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_7:
        SimpleAudioEngine::getInstance()->playEffect("piano/57!.wav");
        break;
	case cocos2d::EventKeyboard::KeyCode::KEY_8:
		SimpleAudioEngine::getInstance()->playEffect("piano/61!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_9:
		SimpleAudioEngine::getInstance()->playEffect("piano/62!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_0:
		SimpleAudioEngine::getInstance()->playEffect("piano/63!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_MINUS:
		SimpleAudioEngine::getInstance()->playEffect("piano/64!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_EQUAL:
		SimpleAudioEngine::getInstance()->playEffect("piano/65!.wav");
		break;


	case cocos2d::EventKeyboard::KeyCode::KEY_Q:
		SimpleAudioEngine::getInstance()->playEffect("piano/41!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		SimpleAudioEngine::getInstance()->playEffect("piano/42!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_E:
		SimpleAudioEngine::getInstance()->playEffect("piano/43!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_R:
		SimpleAudioEngine::getInstance()->playEffect("piano/44!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_T:
		SimpleAudioEngine::getInstance()->playEffect("piano/45!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_Y:
		SimpleAudioEngine::getInstance()->playEffect("piano/46!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_U:
		SimpleAudioEngine::getInstance()->playEffect("piano/47!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_I:
		SimpleAudioEngine::getInstance()->playEffect("piano/51!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_O:
		SimpleAudioEngine::getInstance()->playEffect("piano/52!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_P:
		SimpleAudioEngine::getInstance()->playEffect("piano/53!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_BRACKET:
		SimpleAudioEngine::getInstance()->playEffect("piano/54!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_BRACKET:
		SimpleAudioEngine::getInstance()->playEffect("piano/55!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BACK_SLASH:
		SimpleAudioEngine::getInstance()->playEffect("piano/56!.wav");
		break;


	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		SimpleAudioEngine::getInstance()->playEffect("piano/31!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		SimpleAudioEngine::getInstance()->playEffect("piano/32!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		SimpleAudioEngine::getInstance()->playEffect("piano/33!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F:
		SimpleAudioEngine::getInstance()->playEffect("piano/34!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_G:
		SimpleAudioEngine::getInstance()->playEffect("piano/35!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_H:
		SimpleAudioEngine::getInstance()->playEffect("piano/36!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		SimpleAudioEngine::getInstance()->playEffect("piano/37!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		SimpleAudioEngine::getInstance()->playEffect("piano/41!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_L:
		SimpleAudioEngine::getInstance()->playEffect("piano/42!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SEMICOLON :
		SimpleAudioEngine::getInstance()->playEffect("piano/43!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_APOSTROPHE:
		SimpleAudioEngine::getInstance()->playEffect("piano/44!.wav");
		break;


	case cocos2d::EventKeyboard::KeyCode::KEY_Z:
		SimpleAudioEngine::getInstance()->playEffect("piano/21!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_X:
		SimpleAudioEngine::getInstance()->playEffect("piano/22!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_C:
		SimpleAudioEngine::getInstance()->playEffect("piano/23!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_V:
		SimpleAudioEngine::getInstance()->playEffect("piano/24!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_B:
		SimpleAudioEngine::getInstance()->playEffect("piano/25!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_N:
		SimpleAudioEngine::getInstance()->playEffect("piano/26!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_M:
		SimpleAudioEngine::getInstance()->playEffect("piano/27!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_COMMA:
		SimpleAudioEngine::getInstance()->playEffect("piano/31!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_PERIOD:
		SimpleAudioEngine::getInstance()->playEffect("piano/32!.wav");
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SLASH:
		SimpleAudioEngine::getInstance()->playEffect("piano/33!.wav");
		break;
    default:
        break;
    }
}