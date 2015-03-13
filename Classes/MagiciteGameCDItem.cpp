#include "MagiciteGameCDItem.h"
#include "MagiciteItem.h"

USING_NS_CC;

MagiciteGameCDItem::MagiciteGameCDItem()
:_itemView(nullptr), _cd(0.0f), _is_cd(false)
{

}

MagiciteGameCDItem::~MagiciteGameCDItem()
{

}

void MagiciteGameCDItem::activate()
{
    if (_itemView != nullptr)
    {
        MenuItem::activate();
        
    }
}

void MagiciteGameCDItem::setItemView(MagiciteItem* item)
{
    if (item != nullptr)
    {
        _itemView = item;
        item->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
        this->addChild(item);
    }
}

void MagiciteGameCDItem::eraseItemView()
{
    if (_itemView != nullptr)
    {
        _itemView->removeFromParentAndCleanup(true);
        _itemView = nullptr;
        _cd = 0.0f;
        _is_cd = false;
    }
}

bool MagiciteGameCDItem::init()
{
    if (!MenuItem::initWithCallback((const ccMenuCallback&)nullptr))
    {
        return false;
    }

    auto cd_sprite = Sprite::create("img\\Magicite\\Item\\cd.png");
    _cdView = ProgressTimer::create(cd_sprite);
    _cdView->setReverseProgress(true);
    _cdView->setType(ProgressTimer::Type::RADIAL);
    _cdView->setOpacity(180);
    _cdView->setVisible(false);
    this->addChild(_cdView, 1);

    return true;
}

void MagiciteGameCDItem::startCd(float n)
{
    if (_is_cd)
    {
        this->setEnabled(false);
        _cdView->setVisible(true);

        _cdView->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
        _cdView->setScale(getContentSize().width / 100, getContentSize().height / 100);

        auto progressAction = ProgressFromTo::create(n, 0.0f, 100.0f);
        auto progressCallback = CallFunc::create([this](){
            this->setEnabled(true);
            _cdView->setVisible(false);
        });
        _cdView->runAction(Sequence::create(progressAction, progressCallback, nullptr));
    }
}

void MagiciteGameCDItem::setCD(float n)
{
    _cd = n;
}

float MagiciteGameCDItem::getCD() const
{
    return _cd;
}

void MagiciteGameCDItem::setCDEnable(bool state)
{
    _is_cd = state;
}
bool MagiciteGameCDItem::getCdEnable() const
{
    return _is_cd;
}