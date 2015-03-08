#include "MagiciteSkillCardSpeedUp.h"
#include "MagiciteEffectSpeedUp.h"

MagiciteSkillCardSpeedUp::MagiciteSkillCardSpeedUp()
{

}

MagiciteSkillCardSpeedUp::~MagiciteSkillCardSpeedUp()
{

}

bool MagiciteSkillCardSpeedUp::init()
{
    if (!MagiciteForeverSkillCard::initWithFile("img\\Magicite\\Item\\speedup.png"))
    {
        return false;
    }

    setEffect(MagiciteEffectSpeedUp::create());
    setCd(_effect->getCD());

    return true;
}

MagiciteItem* MagiciteSkillCardSpeedUp::clone()
{
    return create();
}