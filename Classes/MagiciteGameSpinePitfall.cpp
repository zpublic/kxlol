#include "MagiciteGameSpinePitfall.h"

USING_NS_CC;

MagiciteGameSpinePitfall::MagiciteGameSpinePitfall()
{

}

bool MagiciteGameSpinePitfall::init()
{
    if (!MagiciteGamePitfall::initWithFile("CloseNormal.png"))
    {
        return false;
    }
    return true;
}
