#include "MagiciteGameDefaultPortal.h"

MagiciteGameDefaultPortal::MagiciteGameDefaultPortal()
{

}

MagiciteGameDefaultPortal::~MagiciteGameDefaultPortal()
{

}

bool MagiciteGameDefaultPortal::init()
{
    if (!MagiciteGamePortal::initWithFile("img\\Magicite\\Portal\\portal_default.png"))
    {
        return false;
    }

    return true;
}