#include "MagiciteEffectAcid.h"
#include "MagiciteGameAcid.h"
#include "MagiciteGamePhyLayer.h"
#include "MagiciteGaemFactoryMethod.h"

USING_NS_CC;

MagiciteEffectAcid::MagiciteEffectAcid()
{

}

void MagiciteEffectAcid::positive(MagiciteGameObject* obj)
{
    auto moveable = static_cast<MagiciteGameMoveAbleLiving*>(obj);
    MagiciteGameAmmo* ammo = MagiciteGaemFactoryMethod::createAmmo(MagiciteGaemFactoryMethod::Acid);

    ammo->setPosition(obj->getPosition());
    _phyLayer->createPhyBody(ammo, false);
    ammo->getBody()->SetLinearVelocity(b2Vec2(0, 10));
    _phyLayer->addChild(ammo);
    ammo->Move(moveable->getDire());
}

MagiciteEffectAcid* MagiciteEffectAcid::create(MagiciteGamePhyLayer* phyLayer)
{
    auto ptr = new MagiciteEffectAcid();
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

bool MagiciteEffectAcid::init(MagiciteGamePhyLayer* phyLayer)
{
    _phyLayer = phyLayer;

    return true;
}