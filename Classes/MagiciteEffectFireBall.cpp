#include "MagiciteEffectFireBall.h"

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

MagiciteEffectFireBall* MagiciteEffectFireBall::create(const Vec2& pos, MagiciteGamePhyLayer* phyLayer, MagiciteGameMoveAble::Direction dire)
{
    auto ptr = new MagiciteEffectFireBall();
    if (ptr && ptr->init(pos, phyLayer, dire))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteEffectFireBall::init(const Vec2& pos, MagiciteGamePhyLayer* phyLayer, MagiciteGameMoveAble::Direction dire)
{
    _pos = pos;
    _phyLayer = phyLayer;
    _dire = dire;

    return true;
}