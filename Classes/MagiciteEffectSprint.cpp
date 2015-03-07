#include "MagiciteEffectSprint.h"
#include "MagiciteGameMoveAbleLiving.h"

USING_NS_CC;

MagiciteEffectSprint::MagiciteEffectSprint()
{

}

void MagiciteEffectSprint::positive(MagiciteGameObject* obj)
{
    auto _moveable = static_cast<MagiciteGameMoveAbleLiving*>(obj);

    if (_moveable != nullptr)
    {
        _base_sprint_speed = _moveable->getBaseSpeed();
        _step_speed = 0.1f * _base_sprint_speed * (sprint_speed_seed - 1);

        if (!_moveable->_buff_map[Sprint_Tag])
        {
            _moveable->setSpeed(_base_sprint_speed * sprint_speed_seed);
            _moveable->schedule([_moveable,this](float){

                if (_moveable->getSpeed() - 0.00005f <= _base_sprint_speed)
                {
                    _moveable->unschedule("Sprint_key");
                    _moveable->_buff_map[Sprint_Tag] = false;
                }
                else
                {
                    _moveable->setSpeed(_moveable->getSpeed() - _step_speed);
                }
            }, 0.1f, "Sprint_key");
            _moveable->_buff_map[Sprint_Tag] = true;
        }
        else
        {
            _moveable->setSpeed(_base_sprint_speed * sprint_speed_seed);
        }
    }
}

void MagiciteEffectSprint::negative()
{

}

bool MagiciteEffectSprint::init()
{
    // do something
    setCd(cool_down);

    return true;
}