#include "MagiciteDialogue.h"
#include <ui/CocosGUI.h>
#include "base/SystemConfig.h"

bool MagiciteDialogue::init(unsigned long storyId)
{
    if(!cocos2d::Layer::init())
        return false;

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    auto dialog = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 255), visibleSize.width, 200.0f);
    dialog->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
    this->addChild(dialog);

    auto valueMap = cocos2d::FileUtils::getInstance()->getValueMapFromFile("text/story.plist");
    auto str = valueMap.find("story_2")->second.asString();


    auto lblStory = cocos2d::Label::createWithSystemFont(str, kxlol::SystemConfig::GetSystemFont(), 24);
    lblStory->setDimensions(visibleSize.width - 100.0f, 0.0f);
    lblStory->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
    lblStory->setPosition( visibleSize.width / 2.0f,  100.0f);
    dialog->addChild(lblStory);

    auto btnBg = cocos2d::ui::Button::create("img/_blank.png");
    this->addChild(btnBg);
    btnBg->setPosition(cocos2d::Vec2(visibleSize.width / 2,visibleSize.height / 2));
    btnBg->setZoomScale(1.0f);
    btnBg->setScale(visibleSize.width / btnBg->getContentSize().width,
        visibleSize.height / btnBg->getContentSize().height);

    auto avatar = cocos2d::Sprite::create("img/avatar/1.png");
    avatar->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
    this->addChild(avatar);
    avatar->setPosition(0.0f, 200.0f);

    btnBg->addClickEventListener([this](Ref*){
        this->runAction(cocos2d::RemoveSelf::create());    
    });

    return true;
}

MagiciteDialogue* MagiciteDialogue::create( unsigned long storyId )
{
    auto layer = new MagiciteDialogue;
    if (layer && layer->init(storyId))
    {
        layer->autorelease();

        return layer;
    }
    else
    {
        CC_SAFE_DELETE(layer);
        return nullptr;
    }
}
