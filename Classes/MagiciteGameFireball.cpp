#include "MagiciteGameFireball.h"

USING_NS_CC;

MagiciteGameFireball::MagiciteGameFireball()
{

}

bool MagiciteGameFireball::init()
{
    if (!MagiciteGameAmmo::initWithFile("img\\Magicite\\Ammo\\fireball0.png"))
    {
        return false;
    }

    setSpeed(10);

    return true;
}

void MagiciteGameFireball::Move(Direction dire)
{
    setFlippedX(dire == Direction::left);
    setBodyXSpeed(_speed * dire);
    startAnimation(AnimationTag::Move_Tag);
    setState(State::S_Move, true);
}

void MagiciteGameFireball::Stop()
{

}

void MagiciteGameFireball::Jump()
{

}

void MagiciteGameFireball::JumpOver()
{

}

void MagiciteGameFireball::initAnimation()
{

}

void MagiciteGameFireball::startAnimation(AnimationTag tag)
{

}

void MagiciteGameFireball::stopAnimation(AnimationTag tag)
{

}

void MagiciteGameFireball::setBodyXSpeed(float x_speed)
{
    getBody()->SetLinearVelocity(b2Vec2(x_speed, getBody()->GetLinearVelocity().y));
}