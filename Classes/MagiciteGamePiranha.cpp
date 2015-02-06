#include "MagiciteGamePiranha.h"

USING_NS_CC;

MagiciteGamePiranha::MagiciteGamePiranha()
:MagiciteGameLiving(NormalLiving,Piranha)
{

}

void MagiciteGamePiranha::useSkill(int skillId)
{

}

void MagiciteGamePiranha::useSkillEx()
{

}

bool MagiciteGamePiranha::init()
{
    if (!MagiciteGameLiving::initWithFile("CloseSelected"))
    {
        return false;
    }
    return true;
}
