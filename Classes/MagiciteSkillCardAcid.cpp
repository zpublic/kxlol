#include "MagiciteSkillCardAcid.h"
#include "MagiciteEffectAcid.h"

MagiciteSkillCardAcid::MagiciteSkillCardAcid()
{

}

MagiciteSkillCardAcid::~MagiciteSkillCardAcid()
{

}

MagiciteSkillCardAcid* MagiciteSkillCardAcid::create(MagiciteGamePhyLayer* phyLayer)
{
    auto ptr = new MagiciteSkillCardAcid();
    if (ptr && ptr->init(phyLayer))
    {
        ptr->autorelease();
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteSkillCardAcid::init(MagiciteGamePhyLayer* phyLayer)
{
    if (!MagiciteForeverSkillCard::initWithFile("img\\Magicite\\Item\\acid.png"))
    {
        return false;
    }

    setEffect(MagiciteEffectAcid::create(phyLayer));

    _phyLayer = phyLayer;

    return true;
}

MagiciteItem* MagiciteSkillCardAcid::clone()
{
    return create(_phyLayer);
}