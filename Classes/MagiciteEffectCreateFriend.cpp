#include "MagiciteEffectCreateFriend.h"

USING_NS_CC;

MagiciteEffectCreateFriend::MagiciteEffectCreateFriend(
    const Vec2& pos,
    MagiciteGamePhyLayer* phyLayer,
    MagiciteGameMoveAble::Direction dire,
    LivingType type)
    :_pos(pos), _phyLayer(phyLayer), _dire(dire), _type(type)
{

}

void MagiciteEffectCreateFriend::positive()
{
    MagiciteGameMoveAbleLiving* friends = MagiciteGaemFactoryMethod::createFriend(
        MagiciteGaemFactoryMethod::Slime,
        (_dire == MagiciteGameMoveAbleLiving::Direction::left ? true : false));
    friends->setPosition(_pos);

    _phyLayer->createPhyBody(
        friends,
        false,
        Category::DEFAULT_FRIEND,
        Category::DEFAULT_GROUND | Category::DEFAULT_ENEMY | Category::DEFAULT_PITFALL | Category::DEFAULT_HOLE);
    _phyLayer->addChild(friends);
    friends->Move(friends->getDire());

    delete this;
}