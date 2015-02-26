#include "MagiciteEffectSprint.h"

USING_NS_CC;

MagiciteEffectSprint::MagiciteEffectSprint()
{

}

void MagiciteEffectSprint::positive(MagiciteGameObject* obj)
{
    auto _moveable = static_cast<MagiciteGameMoveAbleLiving*>(obj);

    if (_moveable != nullptr)
    {
        if (!_moveable->_buff_map[Sprint_Tag])
        {
            _base_sprint_speed = _moveable->getBaseSpeed();
            _sprint_speed = _base_sprint_speed * 2;
            _moveable->setSpeed(_base_sprint_speed + _sprint_speed);

            _moveable->schedule([_moveable,this](float){

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

MagiciteEffectSprint* MagiciteEffectSprint::create()
{
    auto ptr = new MagiciteEffectSprint();
    if (ptr && ptr->init())
    {
        return ptr;
    }
    else
    {
        CC_SAFE_DELETE(ptr);
        return nullptr;
    }
}

bool MagiciteEffectSprint::init()
{
    // do something

    return true;
}