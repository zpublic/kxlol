#include "MagiciteGameAmmo.h"

USING_NS_CC;

MagiciteGameAmmo::MagiciteGameAmmo()
:MagiciteGameObject(T_Ammo)
{

}

bool MagiciteGameAmmo::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }
    this->initParticle();
    return true;
}

bool MagiciteGameAmmo::initWithFile(const char* filename)
{
    if (!MagiciteGameObject::initWithFile(filename))
    {
        return false;
    }
    this->initParticle();
    return true;
}

void MagiciteGameAmmo::setBodyXSpeed(float x_speed)
{
    getBody()->SetLinearVelocity(b2Vec2(x_speed, getBody()->GetLinearVelocity().y));
}

void MagiciteGameAmmo::setBodyYSpeed(float y_speed)
{
    getBody()->SetLinearVelocity(b2Vec2(getBody()->GetLinearVelocity().x, y_speed));
}