#include "MagiciteScene.h"
int MagiciteScene::LevelNumber = 0;

USING_NS_CC;

bool MagiciteScene::init(int level)
{
    if ( !Scene::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    LevelNumber = level;

    auto valueMap = FileUtils::getInstance()->getValueMapFromFile("text/story.plist");
    auto str =  valueMap.find("story_1")->second.asString();

    auto lblStory = Label::createWithBMFont( "fonts/Chinese.fnt", str); 
    lblStory->setDimensions(visibleSize.width - 100.0f, 0.0f);
    lblStory->setAnchorPoint(Vec2(0.5f, 0.5f));
    lblStory->setPosition(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height / 2.0f);
    this->addChild(lblStory);
    lblStory->setOpacity(0);

    Vector<FiniteTimeAction*> actions;
    actions.pushBack(FadeIn::create(0.3f));
    actions.pushBack(DelayTime::create(str.length() * 0.01f));
    actions.pushBack(FadeOut::create(0.2f));
    actions.pushBack(CallFunc::create([&](){
        this->addChild(MagiciteGameLayer::create());
    }));
    actions.pushBack(RemoveSelf::create(true));
    lblStory->runAction(Sequence::create(actions));
    
    return true;    
}

MagiciteScene* MagiciteScene::create(int level)
{
    auto ptr = new MagiciteScene();
    if (ptr && ptr->init(level))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}
