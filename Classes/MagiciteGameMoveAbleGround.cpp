#include "MagiciteGameMoveAbleGround.h"

USING_NS_CC;

MagiciteGameMoveAbleGround::MagiciteGameMoveAbleGround()
{

}

MagiciteGameMoveAbleGround::~MagiciteGameMoveAbleGround()
{

}

bool MagiciteGameMoveAbleGround::init()
{
    if (!MagiciteGameGround::initWithFile("img\\Magicite\\map\\fragile_ground.png"))
    {
        return false;
    }

    setSpeed(ground_speed);

    return true;
}

bool MagiciteGameMoveAbleGround::initWithFile(const char* filename)
{
    if (!MagiciteGameGround::initWithFile(filename))
    {
        return false;
    }

    setSpeed(ground_speed);

    return true;
}

void MagiciteGameMoveAbleGround::setBodyXSpeed(float x_speed)
{
    getBody()->SetLinearVelocity(b2Vec2(x_speed, getBody()->GetLinearVelocity().y));
}

void MagiciteGameMoveAbleGround::setBodyYSpeed(float y_speed)
{
    getBody()->SetLinearVelocity(b2Vec2(getBody()->GetLinearVelocity().x, y_speed));
}

Vec2 MagiciteGameMoveAbleGround::getPos()
{
    return this->getPosition();
}
