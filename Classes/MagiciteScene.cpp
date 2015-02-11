#include "MagiciteScene.h"
int MagiciteScene::LevelNumber = 0;

USING_NS_CC;

bool MagiciteScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto valueMap = FileUtils::getInstance()->getValueMapFromFile("text/story.plist");
    auto str =  valueMap.find("story_1")->second.asString();

    auto lblStory = Label::createWithBMFont( "fonts/Chinese.fnt", str); 
    lblStory->setDimensions(visibleSize.width - 100.0f, 0.0f);
    lblStory->setAnchorPoint(Vec2(0.5f, 0.5f));
    lblStory->setPosition(origin.x + visibleSize.width / 2.0f, origin.y + visibleSize.height / 2.0f);
    this->addChild(lblStory);
    lblStory->setOpacity(0);

    //添加一个透明的按钮与视图等大的按钮来响应点击屏幕的消息
    auto btnBg = ui::Button::create("img/_blank.png");
    this->addChild(btnBg);
    btnBg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    btnBg->setZoomScale(1.0f);
    btnBg->setScale(visibleSize.width / btnBg->getContentSize().width, 
        visibleSize.height / btnBg->getContentSize().height);
    
    Vector<FiniteTimeAction*> actionIn;
    Vector<FiniteTimeAction*> actionOut;
    actionIn.pushBack(FadeIn::create(0.3f));
    actionIn.pushBack(DelayTime::create(str.length() * 0.01f));
    actionOut.pushBack(CallFunc::create([btnBg](){
        btnBg->setEnabled(false);
    }));
    actionOut.pushBack(FadeOut::create(0.2f));
    actionOut.pushBack(CallFunc::create([this, btnBg](){
        btnBg->runAction(RemoveSelf::create());
        this->addChild(MagiciteGameLayer::create());
    }));
    actionOut.pushBack(RemoveSelf::create(true));
    actionIn.pushBack(Sequence::create(actionOut));
    lblStory->runAction(Sequence::create(actionIn));

    btnBg->addTouchEventListener([lblStory, actionOut](Ref*, ui::Widget::TouchEventType eve){
        if(eve == ui::Widget::TouchEventType::BEGAN){
            lblStory->stopAllActions();
            lblStory->runAction(Sequence::create(actionOut));
        }
    });
    
    return true;    
}

MagiciteScene* MagiciteScene::create()
{
    auto ptr = new MagiciteScene();
    if (ptr && ptr->init())
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

void MagiciteScene::setLevel(int level)
{
    LevelNumber = level;
}

int MagiciteScene::getLevel()
{
    return LevelNumber;
}
