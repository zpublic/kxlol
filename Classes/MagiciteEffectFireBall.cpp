#include "MagiciteEffectFireBall.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGameFireball.h"
#include "MagiciteGameFactoryMethod.h"

USING_NS_CC;

MagiciteEffectFireBall::MagiciteEffectFireBall()
{

}

void MagiciteEffectFireBall::positive(MagiciteGameObject* obj)
{
    auto moveable = static_cast<MagiciteGameMoveAbleLiving*>(obj);
    MagiciteGameAmmo* ammo = MagiciteGameFactoryMethod::createAmmo(MagiciteGameFactoryMethod::FireBall);

    ammo->setPosition(obj->getPosition());
    _phyLayer->createPhyBody(ammo, false);
    ammo->getBody()->SetGravityScale(0.0f);
    _phyLayer->addChild(ammo);
    ammo->Move(moveable->getDire());
}

MagiciteEffectFireBall* MagiciteEffectFireBall::create(MagiciteGamePhyLayer* phyLayer)
{
    auto ptr = new MagiciteEffectFireBall();
    if (ptr && ptr->init(phyLayer))
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

bool MagiciteEffectFireBall::init(MagiciteGamePhyLayer* phyLayer)
{
    _phyLayer = phyLayer;

    return true;
}