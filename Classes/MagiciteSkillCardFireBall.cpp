#include "MagiciteSkillCardFireBall.h"
#include "MagiciteEffectFireBall.h"

MagiciteSkillCardFireBall::MagiciteSkillCardFireBall()
{

}

MagiciteSkillCardFireBall::~MagiciteSkillCardFireBall()
{

}

MagiciteSkillCardFireBall* MagiciteSkillCardFireBall::create(MagiciteGamePhyLayer* phyLayer)
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

bool MagiciteSkillCardFireBall::init(MagiciteGamePhyLayer* phyLayer)
{
    if (!MagiciteForeverSkillCard::initWithFile("img\\Magicite\\Item\\fireball.png"))
    {
        return false;
    }

    setEffect(MagiciteEffectFireBall::create(phyLayer));
    setCd(_effect->getCD());

    _phyLayer = phyLayer;

    return true;
}

MagiciteItem* MagiciteSkillCardFireBall::clone()
{
    return create(_phyLayer);
}