#include "MagiciteEffectSpeedUp.h"
#include "MagiciteGameMoveAbleLiving.h"

USING_NS_CC;

MagiciteEffectSpeedUp::MagiciteEffectSpeedUp()
{

}

void MagiciteEffectSpeedUp::positive(MagiciteGameObject* obj)
{
    auto _moveable = static_cast<MagiciteGameMoveAbleLiving*>(obj);

    if (_moveable != nullptr)
    {
        _old_speed = _moveable->getBaseSpeed();

        auto action = Sequence::create(DelayTime::create(3), CallFunc::create([_moveable,this]()
        {
            if (_moveable->getSpeed() - _old_speed + 0.00005 > _old_speed)
            {
                _moveable->setSpeed(_moveable->getSpeed() - _old_speed);
            }
            _moveable->_buff_map[Speed_Up] = false;

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

bool MagiciteEffectSpeedUp::init()
{
    // do something
    setCd(cool_down);

    return true;
}