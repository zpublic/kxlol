#include "MagiciteGameLiving.h"

USING_NS_CC;

MagiciteGameLiving::MagiciteGameLiving(
    MoveAbleType movetype/* = NormalLiving*/,
    LivingType livingtype/* = Unknow*/)
    :MagiciteGameObject(Type::T_Living), LivingMoveType(movetype), NormalLivingType(livingtype)
{

}

bool MagiciteGameLiving::init()
{
    if (!MagiciteGameObject::init())
    {
        return false;
    }
    return false;
}

bool MagiciteGameLiving::initWithFile(const char* filename)
{
    if (!MagiciteGamePhySprite::initWithFile(filename))
    {
        return false;
    }
    return true;
}