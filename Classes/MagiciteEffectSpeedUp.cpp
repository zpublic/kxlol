#include "MagiciteEffectSpeedUp.h"

USING_NS_CC;

MagiciteEffectSpeedUp::MagiciteEffectSpeedUp(MagiciteGameMoveAbleLiving* moveable)
:_moveable(moveable)
{

}
void MagiciteEffectSpeedUp::positive()
{
    if (_moveable != nullptr)
    {
        _old_speed = _moveable->getBaseSpeed();

        auto action = Sequence::create(DelayTime::create(3), CallFunc::create([&]()
        {
            if (_moveable->getSpeed() - _old_speed + 0.00005 > _old_speed)
            {
                _moveable->setSpeed(_moveable->getSpeed() - _old_speed);
            }
            _moveable->_buff_map[Speed_Up] = false;

            delete this;
        }), nullptr);
        action->setTag(Speed_Up);
        if (!_moveable->_buff_map[Speed_Up])
        {
            _moveable->setSpeed(_old_speed + _old_speed);
            _moveable->_buff_map[Speed_Up] = true;
        }
        else
        {
            _moveable->stopAllActionsByTag(Speed_Up);
        }
        _moveable->runAction(action);
    }
    //MagiciteEffectValueChange.positive
    //timer-negative

}

void MagiciteEffectSpeedUp::negative()
{
    ///> 这儿不需要做啥 交给timer来取消效果
}

