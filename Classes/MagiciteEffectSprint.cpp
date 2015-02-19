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
        if (!_moveable->_buff_map[Sprint_Tag])
        {
            _base_sprint_speed = _moveable->getBaseSpeed();
            _sprint_speed = _base_sprint_speed * 2;
            _moveable->setSpeed(_base_sprint_speed + _sprint_speed);

            _moveable->schedule([&](float){

                if (_sprint_speed - 0.00005f <= 0.0f || _moveable->getSpeed() - 0.00005f <= _base_sprint_speed)
                {
                    _moveable->unschedule("Sprint_key");
                    _moveable->_buff_map[Sprint_Tag] = false;
                }
                else
                {
                    _sprint_speed -= 0.5f;
                    _moveable->setSpeed(_moveable->getSpeed() - 0.5f);
                }
            }, 0.2f, "Sprint_key");
            _moveable->_buff_map[Sprint_Tag] = true;
        }
        else
        {
            _sprint_speed = _base_sprint_speed * 2;
            _moveable->setSpeed(_base_sprint_speed + _sprint_speed);
        }
    }
}

void MagiciteEffectSprint::negative()
{

}