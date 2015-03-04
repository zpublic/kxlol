#include "MagiciteEffectCreateFriend.h"
#include "MagiciteGamePhyLayer.h"

USING_NS_CC;

MagiciteEffectCreateFriend::MagiciteEffectCreateFriend()
{

}

void MagiciteEffectCreateFriend::positive(MagiciteGameObject* obj)
{
    auto moveable = static_cast<MagiciteGameMoveAbleLiving*>(obj);
    MagiciteGameMoveAbleLiving* friends = MagiciteGaemFactoryMethod::createFriend(
        _type,
        (moveable->getDire() == MagiciteGameMoveAbleLiving::Direction::left ? true : false));
    friends->setPosition(obj->getPosition());

    _phyLayer->createPhyBody(
        friends,
        false);
    _phyLayer->addChild(friends);
    friends->Move(friends->getDire());

}

MagiciteEffectCreateFriend* MagiciteEffectCreateFriend::create(   
    MagiciteGamePhyLayer* phyLayer,
    LivingType type)
{
    auto ptr = new MagiciteEffectCreateFriend();
    if (ptr && ptr->init(phyLayer, type))
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
    MagiciteGamePhyLayer* phyLayer,
    LivingType type)
{
    _phyLayer = phyLayer;
    _type = type;

    return true;
}