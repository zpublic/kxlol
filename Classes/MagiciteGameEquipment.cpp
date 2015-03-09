#include "MagiciteGameEquipment.h"


bool MagiciteGameEquipment::init()
{
    if(!Node::init())
        return false;

    auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    auto title = cocos2d::Label::createWithTTF("Equip", "fonts/Marker Felt.ttf", 32);
    title->setPosition(200.0f, 520.0f);
    title->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    auto bg = cocos2d::LayerColor::create(cocos2d::Color4B(0x00, 0x00, 0x00, 0xff), 402.0f, 552.0f);
    bg->setPosition(-201.0f - visibleSize.width / 4, -276.0f);

    bg->addChild(title);
    this->addChild(bg);

    auto player = cocos2d::Sprite::create("img/Magicite/enemy/chicken_stop.png");
    player->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    player->setPosition(200.0f, 250.0f);
    bg->addChild(player);

    for(int i = 0; i < 8; i++)
    {
        auto box = cocos2d::LayerColor::create(cocos2d::Color4B(0xee, 0xee, 0xee, 0x80), 48.0f, 48.0f);
        box->setPosition(20.0f + (i % 2)*310.0f, 80.0f + (i / 2) * 100.0f);
        bg->addChild(box);
    }

    return true;
}
