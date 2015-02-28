#include "MagiciteSkillCardFireBall.h"
#include "MagiciteEffectFireBall.h"

MagiciteSkillCardFireBall::MagiciteSkillCardFireBall()
{

}

MagiciteSkillCardFireBall::~MagiciteSkillCardFireBall()
{

}

MagiciteSkillCardFireBall* MagiciteSkillCardFireBall::create(
    const cocos2d::Vec2& pos,
    MagiciteGamePhyLayer* phyLayer,
    MagiciteGameMoveAble::Direction dire)
{
    auto ptr = new MagiciteSkillCardFireBall();
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

bool MagiciteSkillCardFireBall::init(
    const cocos2d::Vec2& pos,
    MagiciteGamePhyLayer* phyLayer,
    MagiciteGameMoveAble::Direction dire)
{
    _effect = MagiciteEffectFireBall::create(pos, phyLayer, dire);

    return true;
}