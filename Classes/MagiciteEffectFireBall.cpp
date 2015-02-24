#include "MagiciteEffectFireBall.h"

USING_NS_CC;

MagiciteEffectFireBall::MagiciteEffectFireBall(const Vec2& pos, MagiciteGamePhyLayer* phyLayer, MagiciteGameMoveAble::Direction dire)
:_pos(pos), _phyLayer(phyLayer), _dire(dire)
{

}

void MagiciteEffectFireBall::positive()
{
    MagiciteGameAmmo* ammo = nullptr;
    if (rand() % 5 == 0)
    {
        ammo = MagiciteGaemFactoryMethod::createAmmo(MagiciteGaemFactoryMethod::Acid);
        ammo->setPosition(_pos);
        _phyLayer->createPhyBody(ammo, false, Category::DEFAULT_AMMO, Category::DEFAULT_ENEMY | Category::DEFAULT_GROUND);
        ammo->getBody()->SetLinearVelocity(b2Vec2(0, 10));
    }
    else
    {
        ammo = MagiciteGaemFactoryMethod::createAmmo(MagiciteGaemFactoryMethod::FireBall);
        ammo->setPosition(_pos);
        _phyLayer->createPhyBody(ammo, false, Category::DEFAULT_AMMO, Category::DEFAULT_ENEMY | Category::DEFAULT_GROUND);
        ammo->getBody()->SetGravityScale(0.0f);
    }
    _phyLayer->addChild(ammo);
    ammo->Move(_dire);
    
    delete this;
}