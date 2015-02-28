#include "MagiciteGameLiving.h"
#include "MagiciteEffect.h"

USING_NS_CC;

MagiciteGameLiving::MagiciteGameLiving(
    MoveAbleType movetype/* = NormalLiving*/,
    LivingType livingtype/* = Unknow*/)
    :MagiciteGameObject(Type::T_Living), LivingMoveType(movetype), NormalLivingType(livingtype)
{
    _health_point = 0;
    _mana_point = 0;;
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

void MagiciteGameLiving::setHP(int hp)
{
    _health_point = hp;
}

int MagiciteGameLiving::getHP() const
{
    return _health_point;
}

void MagiciteGameLiving::setMP(int mp)
{
    _mana_point = mp;
}

int MagiciteGameLiving::getMP() const
{
    return _mana_point;
}

void MagiciteGameLiving::attact(int damage/* = 1*/)
{
   _health_point -= damage;
}

void MagiciteGameLiving::useSkill(MagiciteEffect* effect)
{
    effect->positive(this);
}