#include "MagiciteGameShowLayer.h"
#include "base\SystemConfig.h"

USING_NS_CC;

bool MagiciteGameShowLayer::init(float TimeDelta, const std::string& str)
{
    if (!Layer::init())
    {
        return false;
    }

    _timeDelta = TimeDelta;

    auto size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    _label = Label::createWithSystemFont(str, kxlol::SystemConfig::GetSystemFont(), 42);
    _label->setPosition(Vec2(origin.x + size.width / 2 ,origin.y + size.height / 2));
    this->addChild(_label);

    return true;
}

MagiciteGameShowLayer* MagiciteGameShowLayer::create(float TimeDelta, const std::string& str)
{
    auto ptr = new MagiciteGameShowLayer();
    if (ptr && ptr->init(TimeDelta, str))
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

void MagiciteGameShowLayer::start()
{
    auto timeOut = DelayTime::create(_timeDelta);
    auto showOut = FadeOut::create(0.3f);
    auto DeleteCallBack = CallFunc::create([this](){
        this->removeFromParentAndCleanup(true);
    });
    auto actionSeq = Sequence::create(timeOut, showOut, DeleteCallBack, nullptr);
    _label->runAction(actionSeq);
}