#include "MagiciteEffectAcid.h"
#include "MagiciteGameAcid.h"
#include "MagiciteGameFactoryMethod.h"
#include "MagiciteGamePhyWorld.h"
#include "MagiciteGameMoveAbleLiving.h"

USING_NS_CC;

MagiciteEffectAcid::MagiciteEffectAcid()
{

}

void MagiciteEffectAcid::positive(MagiciteGameObject* obj)
{
    auto moveable = static_cast<MagiciteGameMoveAbleLiving*>(obj);
    auto world = reinterpret_cast<MagiciteGamePhyWorld*>(obj->getBody()->GetWorld());
    auto layer = obj->getParent();

    MagiciteGameAmmo* ammo = MagiciteGameFactoryMethod::createAmmo(MagiciteGameFactoryMethod::Acid);
    ammo->setPosition(obj->getPosition());
    world->createPhyBody(ammo, false, Magicite::FIXTURE_TYPE_AMMO);
    ammo->getBody()->SetLinearVelocity(b2Vec2(0, 10));
    layer->addChild(ammo);
    ammo->Move(moveable->getDire());
}

bool MagiciteEffectAcid::init()
{
    setCd(1.0f);

    return true;
}