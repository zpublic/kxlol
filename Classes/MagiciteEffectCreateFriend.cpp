#include "MagiciteEffectCreateFriend.h"
#include "MagiciteGamePhyWorld.h"
#include "MagiciteGameMoveAbleLiving.h"

USING_NS_CC;

MagiciteEffectCreateFriend::MagiciteEffectCreateFriend()
{

}

void MagiciteEffectCreateFriend::positive(MagiciteGameObject* obj)
{
    auto moveable = static_cast<MagiciteGameMoveAbleLiving*>(obj);
    auto layer = moveable->getParent();
    auto world = reinterpret_cast<MagiciteGamePhyWorld*>(obj->getBody()->GetWorld());

    MagiciteGameMoveAbleLiving* friends = MagiciteGameFactoryMethod::createFriend(_type);
    friends->setDire(moveable->getDire());
    friends->setPosition(obj->getPosition());

    world->createPhyBody(friends, false, Magicite::FIXTURE_TYPE_FRIEND);
    layer->addChild(friends);
    friends->Move(friends->getDire());

}

MagiciteEffectCreateFriend* MagiciteEffectCreateFriend::create(LivingType type)
{
    auto ptr = new MagiciteEffectCreateFriend();
    if (ptr && ptr->init(type))
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

bool MagiciteEffectCreateFriend::init(
    LivingType type)
{
    _type = type;

    setCd(1.5f);

    return true;
}