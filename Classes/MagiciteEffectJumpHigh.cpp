#include "MagiciteEffectJumpHigh.h"
#include "MagiciteGameMoveAbleLiving.h"

USING_NS_CC;

MagiciteEffectJumpHigh::MagiciteEffectJumpHigh()
{

}

void MagiciteEffectJumpHigh::positive(MagiciteGameObject* obj)
{
    auto _moveable = static_cast<MagiciteGameMoveAbleLiving*>(obj);

    if (_moveable != nullptr)
    {
        auto action = Sequence::create(DelayTime::create(3), CallFunc::create([_moveable,this]()
        {
            _moveable->setJumpHeight(_moveable->getJumpHeight() / 2);
            _moveable->_buff_map[Jump_High] = false;

        }), nullptr);

        action->setTag(Jump_High);
        if (!_moveable->_buff_map[Jump_High])
        {
            _moveable->setJumpHeight(_moveable->getJumpHeight() * 2);
            _moveable->_buff_map[Jump_High] = true;
        }
        else
        {
            _moveable->stopAllActionsByTag(Jump_High);
        }
        _moveable->runAction(action);
    }
}
//MagiciteEffectValueChange.positive
//timer-negative

void MagiciteEffectJumpHigh::negative()
{

}

bool MagiciteEffectJumpHigh::init()
{
    // do something

    return true;
}