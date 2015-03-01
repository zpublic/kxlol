#include "MagiciteEffectFireBall.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGameFireball.h"
#include "MagiciteGaemFactoryMethod.h"

USING_NS_CC;

MagiciteEffectFireBall::MagiciteEffectFireBall()
{

}

void MagiciteEffectFireBall::positive(MagiciteGameObject* obj)
{
    MagiciteGameAmmo* ammo = nullptr;
    if (rand() % 5 == 0)
    {
        ammo = MagiciteGaemFactoryMethod::createAmmo(MagiciteGaemFactoryMethod::Acid);
        ammo->setPosition(obj->getPosition());
        _phyLayer->createPhyBody(ammo, false);
        ammo->getBody()->SetLinearVelocity(b2Vec2(0, 10));
    }
    else
    {
        ammo = MagiciteGaemFactoryMethod::createAmmo(MagiciteGaemFactoryMethod::FireBall);
        ammo->setPosition(obj->getPosition());
        _phyLayer->createPhyBody(ammo, false);
        ammo->getBody()->SetGravityScale(0.0f);
    }
    _phyLayer->addChild(ammo);
    ammo->Move(_dire);
    
    delete this;
}

MagiciteEffectFireBall* MagiciteEffectFireBall::create(MagiciteGamePhyLayer* phyLayer, MagiciteGameMoveAble::Direction dire)
{
    auto ptr = new MagiciteEffectFireBall();
    if (ptr && ptr->init(phyLayer, dire))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteEffectFireBall::init(MagiciteGamePhyLayer* phyLayer, MagiciteGameMoveAble::Direction dire)
{
    _phyLayer = phyLayer;
    _dire = dire;

    return true;
}