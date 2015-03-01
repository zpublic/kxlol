#include "MagiciteEffectCreateFriend.h"
#include "MagiciteGamePhyLayer.h"

USING_NS_CC;

MagiciteEffectCreateFriend::MagiciteEffectCreateFriend()
{

}

void MagiciteEffectCreateFriend::positive(MagiciteGameObject* obj)
{
    MagiciteGameMoveAbleLiving* friends = MagiciteGaemFactoryMethod::createFriend(
        _type,
        (_dire == MagiciteGameMoveAbleLiving::Direction::left ? true : false));
    friends->setPosition(_pos);

    _phyLayer->createPhyBody(
        friends,
        false);
    _phyLayer->addChild(friends);
    friends->Move(friends->getDire());

    delete this;
}

MagiciteEffectCreateFriend* MagiciteEffectCreateFriend::create
(const cocos2d::Vec2& pos,
    MagiciteGamePhyLayer* phyLayer,
    MagiciteGameMoveAble::Direction dire,
    LivingType type)
{
    auto ptr = new MagiciteEffectCreateFriend();
    if (ptr && ptr->init(pos, phyLayer, dire, type))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteEffectCreateFriend::init(
    const cocos2d::Vec2& pos,
    MagiciteGamePhyLayer* phyLayer,
    MagiciteGameMoveAble::Direction dire,
    LivingType type)
{
    _pos = pos;
    _phyLayer = phyLayer;
    _dire = dire;
    _type = type;

    return true;
}