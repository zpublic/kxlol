#include "MagiciteSkillCardSprint.h"
#include "MagiciteEffectSprint.h"

MagiciteSkillCardSprint::MagiciteSkillCardSprint()
{

}

MagiciteSkillCardSprint::~MagiciteSkillCardSprint()
{

}

bool MagiciteSkillCardSprint::init()
{
    if (!MagiciteForeverSkillCard::initWithFile("img\\Magicite\\Item\\sprint.png"))
    {
        return false;
    }

    setEffect(MagiciteEffectSprint::create());

    return true;
}

MagiciteItem* MagiciteSkillCardSprint::clone()
{
    return create();
}