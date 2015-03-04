#include "MagiciteTempSkillCard.h"

std::string MagiciteTempSkillCard::name = "skillcard";

MagiciteTempSkillCard::MagiciteTempSkillCard()
:MagiciteTempItem(life)
{
    setItemName(name);
}

bool MagiciteTempSkillCard::init()
{
    if (!MagiciteTempItem::init())
    {
        return false;
    }
    return true;
}

bool MagiciteTempSkillCard::initWithFile(const char* filename)
{
    if (!MagiciteTempItem::initWithFile(filename))
    {
        return false;
    }
    return true;
}