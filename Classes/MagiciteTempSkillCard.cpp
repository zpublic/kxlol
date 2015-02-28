#include "MagiciteTempSkillCard.h"

std::string MagiciteTempSkillCard::name = "skillcard";

MagiciteTempSkillCard::MagiciteTempSkillCard()
:MagiciteTempItem(life)
{
    setItemName(name);
}

