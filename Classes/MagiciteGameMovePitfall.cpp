#include "MagiciteGameMovePitfall.h"

MagiciteGameMovePitfall::MagiciteGameMovePitfall()
:MagiciteGamePitfall(MagiciteGamePitfall::Meteorite)
{

}

MagiciteGameMovePitfall::~MagiciteGameMovePitfall()
{
    
}

bool MagiciteGameMovePitfall::init()
{
    if (!MagiciteGamePitfall::init())
    {
        return false;
    }

    return true;
}

bool MagiciteGameMovePitfall::initWithFile(const char* filename)
{
    if (!MagiciteGamePitfall::initWithFile(filename))
    {
        return false;
    }

    return true;
}

void MagiciteGameMovePitfall::setBodyXSpeed(float x_speed)
{
    getBody()->SetLinearVelocity(b2Vec2(x_speed, getBody()->GetLinearVelocity().y));
}

void MagiciteGameMovePitfall::setBodyYSpeed(float y_speed)
{
    getBody()->SetLinearVelocity(b2Vec2(getBody()->GetLinearVelocity().x, y_speed));
}