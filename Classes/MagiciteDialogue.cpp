#include "MagiciteDialogue.h"
#include <ui/CocosGUI.h>

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

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
    const char* const fontName = "Microsoft YaHei";
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    const char* const fontName = "Droid Sans Fallback";
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    const char* const fontName = "Heiti SC";
#endif

    //若您的目标系统不是以上的几种系统，请按照以上格式在下面添加您的目标系统和对应的默认字体名称

    //------------------------------------------------------------------------------------------

    auto lblStory = cocos2d::Label::createWithSystemFont(str, fontName, 24);
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
