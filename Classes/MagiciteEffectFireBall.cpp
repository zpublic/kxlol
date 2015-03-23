#include "MagiciteEffectFireBall.h"
#include "MagiciteGamePhyWorld.h"
#include "MagiciteGameFireball.h"
#include "MagiciteGameFactoryMethod.h"
#include "MagiciteGameMoveAbleLiving.h"

USING_NS_CC;

MagiciteEffectFireBall::MagiciteEffectFireBall()
{

}

void MagiciteEffectFireBall::positive(MagiciteGameObject* obj)
{
    auto moveable = static_cast<MagiciteGameMoveAbleLiving*>(obj);
    auto layer = moveable->getParent();
    auto world = reinterpret_cast<MagiciteGamePhyWorld*>(obj->getBody()->GetWorld());

    MagiciteGameAmmo* ammo = MagiciteGameFactoryMethod::createAmmo(MagiciteGameFactoryMethod::FireBall);
    ammo->setPosition(obj->getPosition());
    world->createPhyBody(ammo, false, Magicite::FIXTURE_TYPE_AMMO);
    ammo->getBody()->SetGravityScale(0.0f);
    layer->addChild(ammo);
    ammo->Move(moveable->getDire());
}

bool MagiciteEffectFireBall::init()
{
    setCd(1.0f);

    return true;
}