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
    MagiciteGamePhyLayer* phyLayer)
{
    auto ptr = new MagiciteSkillCardFriend();
    if (ptr && ptr->init(type, phyLayer))
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
    MagiciteGamePhyLayer* phyLayer)
{
    _effect = MagiciteEffectCreateFriend::create(phyLayer, type);

    return true;
}