#include "MagiciteCaptionScene.h"
#include "MagiciteGameLayer.h"
#include "MagiciteScene.h"
#include <ui\CocosGUI.h>
#include "base\SystemConfig.h"

USING_NS_CC;

MagiciteCaptionScene::MagiciteCaptionScene()
{

}

bool MagiciteCaptionScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    _is_ready = false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto valueMap = FileUtils::getInstance()->getValueMapFromFile("text/story.plist");
    auto str = valueMap.find("story_1")->second.asString();

    auto lblStory = Label::createWithSystemFont(str, kxlol::SystemConfig::GetSystemFont(), 24);
    lblStory->setDimensions(visibleSize.width - 100.0f, 0.0f);
    lblStory->setAnchorPoint(Vec2(0.5f, 0.5f));
    lblStory->setPosition(origin.x + visibleSize.width / 2.0f, origin.y - lblStory->getContentSize().height / 2.0f);
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
    actionIn.pushBack(MoveTo::create(str.length() * 0.01f, Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)));
    actionIn.pushBack(CallFunc::create([this](){
        this->_is_ready = true;
    }));
    actionIn.pushBack(DelayTime::create(str.length() * 0.01f));
    actionOut.pushBack(CallFunc::create([btnBg](){
        btnBg->setEnabled(false);
    }));
    actionOut.pushBack(FadeOut::create(0.2f));
    actionOut.pushBack(CallFunc::create([this, btnBg](){
        btnBg->runAction(RemoveSelf::create());
        Director::getInstance()->replaceScene(MagiciteScene::create());
    }));
    actionOut.pushBack(RemoveSelf::create(true));
    actionIn.pushBack(Sequence::create(actionOut));
    lblStory->runAction(Sequence::create(actionIn));

    btnBg->addTouchEventListener([lblStory, actionOut, this, origin, visibleSize, str](Ref*, ui::Widget::TouchEventType eve){
        if (eve == ui::Widget::TouchEventType::BEGAN){
            if (this->_is_ready)
            {
                lblStory->runAction(Sequence::create(actionOut));
            }
            else
            {
                this->_is_ready = true;
                lblStory->stopAllActions();
                lblStory->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

                Vector<FiniteTimeAction*> reAction;
                reAction.pushBack(DelayTime::create(str.length() * 0.01f));
                reAction.pushBack(Sequence::create(actionOut));
                lblStory->runAction(Sequence::create(reAction));
            }
        }
    });

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [lblStory, actionOut, listener](EventKeyboard::KeyCode key, Event* event){
        switch (key)
        {
        case cocos2d::EventKeyboard::KeyCode::KEY_KP_ENTER:
        case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
            lblStory->stopAllActions();
            lblStory->runAction(Sequence::create(actionOut));
            listener->setEnabled(false);
            break;
        default:
            break;
        }

    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}
