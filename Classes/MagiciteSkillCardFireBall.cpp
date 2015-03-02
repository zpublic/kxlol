#include "MagiciteSkillCardFireBall.h"
#include "MagiciteEffectFireBall.h"
#include "MagiciteItemCardObject.h"

MagiciteSkillCardFireBall::MagiciteSkillCardFireBall()
{

}

MagiciteSkillCardFireBall::~MagiciteSkillCardFireBall()
{

}

MagiciteSkillCardFireBall* MagiciteSkillCardFireBall::create(
    MagiciteGamePhyLayer* phyLayer)
{
    auto ptr = new MagiciteSkillCardFireBall();
    if (ptr && ptr->init(phyLayer))
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
    MagiciteGamePhyLayer* phyLayer)
{
    _effect = MagiciteEffectFireBall::create(phyLayer);

    return true;
}

MagiciteGameObject* MagiciteSkillCardFireBall::getItemObject()
{
    return MagiciteItemCardObject::create();
}