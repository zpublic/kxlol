#include "MagiciteGameIncubator.h"

USING_NS_CC;

MagiciteGameIncubator::MagiciteGameIncubator()
{

}

bool MagiciteGameIncubator::init()
{
    if (!MagiciteGamePet::initWithFile("img\\Magicite\\pet\\pet_qb.png"))
    {
        return false;
    }
    return true;
}