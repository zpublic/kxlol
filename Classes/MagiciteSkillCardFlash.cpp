#include "MagiciteSkillCardFlash.h"
#include "MagiciteEffectFlash.h"

MagiciteSkillCardFlash::MagiciteSkillCardFlash()
{

}

MagiciteSkillCardFlash::~MagiciteSkillCardFlash()
{

}

MagiciteSkillCardFlash* MagiciteSkillCardFlash::create(MagiciteGamePhyLayer* phyLayer, float length)
{
    auto ptr = new MagiciteSkillCardFlash();
    if (ptr && ptr->init(phyLayer, length))
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteSkillCardFlash::init(MagiciteGamePhyLayer* phyLayer, float length)
{
    if (!MagiciteForeverSkillCard::initWithFile("img\\Magicite\\Item\\flash.png"))
    {
        return false;
    }

    setEffect(MagiciteEffectFlash::create(phyLayer, length));

    _phyLayer = phyLayer;
    _length = length;

    return true;
}

MagiciteItem* MagiciteSkillCardFlash::clone()
{
    return create(_phyLayer, _length);
}