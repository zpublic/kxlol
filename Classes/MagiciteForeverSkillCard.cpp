#include "MagiciteForeverSkillCard.h"

std::string MagiciteForeverSkillCard::name = "ForeverSkillCard";

MagiciteForeverSkillCard::MagiciteForeverSkillCard()
{
    setItemName(name);
}

bool MagiciteForeverSkillCard::init()
{
    if (!MagiciteForeverItem::init())
    {
        return false;
    }
    return true;
}

bool MagiciteForeverSkillCard::initWithFile(const char* filename)
{
    if (!MagiciteForeverItem::initWithFile(filename))
    {
        return false;
    }
    return true;
}