#include "MagiciteEffectSprint.h"

USING_NS_CC;

MagiciteEffectSprint::MagiciteEffectSprint(MagiciteGameMoveAbleLiving* moveable)
:_moveable(moveable)
{

}

void MagiciteEffectSprint::positive()
{
    if (_moveable != nullptr)
    {
        _old_speed = _moveable->getSpeed();
        _moveable->setSpeed(_old_speed * 3);

        _moveable->schedule([&](float){
            int new_speed = _moveable->getSpeed();
            if (new_speed == _old_speed)
            {
                _moveable->unschedule("Sprint_key");
            }
            else
            {
                _moveable->setSpeed(new_speed - 1);
            }
        }, 1, "Sprint_key");

    }
}

void MagiciteEffectSprint::negative()
{

}