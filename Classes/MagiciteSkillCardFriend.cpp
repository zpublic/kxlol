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

    if (!MagiciteForeverSkillCard::initWithFile("img\\Magicite\\Item\\card.png"))
    {
        return false;
    }

    setEffect(MagiciteEffectCreateFriend::create(phyLayer, type));
    setCd(_effect->getCD());

    _type = type;
    _phyLayer = phyLayer;

    return true;
}

MagiciteItem* MagiciteSkillCardFriend::clone()
{
    return create(_type, _phyLayer);
}