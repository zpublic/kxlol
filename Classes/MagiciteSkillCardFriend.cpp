#include "MagiciteSkillCardFriend.h"
#include "MagiciteEffectCreateFriend.h"

MagiciteSkillCardFriend::MagiciteSkillCardFriend()
{

}

MagiciteSkillCardFriend::~MagiciteSkillCardFriend()
{

}

MagiciteSkillCardFriend* MagiciteSkillCardFriend::create(
    LivingType type,
    MagiciteGamePhyLayer* phyLayer,
    MagiciteGameMoveAble::Direction dire)
{
    auto ptr = new MagiciteSkillCardFriend();
    if (ptr && ptr->init(type, phyLayer, dire))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteSkillCardFriend::init(
    LivingType type,
    MagiciteGamePhyLayer* phyLayer,
    MagiciteGameMoveAble::Direction dire)
{
    _effect = MagiciteEffectCreateFriend::create(phyLayer, dire, type);

    return true;
}