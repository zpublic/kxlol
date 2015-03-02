#include "MagiciteSkillCardFireBall.h"
#include "MagiciteEffectFireBall.h"

MagiciteSkillCardFireBall::MagiciteSkillCardFireBall()
{

}

MagiciteSkillCardFireBall::~MagiciteSkillCardFireBall()
{

}

MagiciteSkillCardFireBall* MagiciteSkillCardFireBall::create(
    MagiciteGamePhyLayer* phyLayer,
    MagiciteGameMoveAble::Direction dire)
{
    auto ptr = new MagiciteSkillCardFireBall();
    if (ptr && ptr->init(phyLayer, dire))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteSkillCardFireBall::init(
    MagiciteGamePhyLayer* phyLayer,
    MagiciteGameMoveAble::Direction dire)
{
    _effect = MagiciteEffectFireBall::create(phyLayer, dire);

    return true;
}