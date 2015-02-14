#include "MagiciteEffectSpeenUp.h"

USING_NS_CC;

MagiciteEffectSpeenUp::MagiciteEffectSpeenUp(MagiciteGameMoveAbleLiving* moveable)
:_moveable(moveable)
{

}
void MagiciteEffectSpeenUp::positive()
{
    if (_moveable != nullptr)
    {
        _moveable->setSpeed(_moveable->getSpeed() * 2);
        _moveable->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([&]()
        {
            log("fuck");
            _moveable->setSpeed(_moveable->getSpeed() / 2);

            delete this;
        }),nullptr));
        
    }
    //MagiciteEffectValueChange.positive
    //timer-negative

}

void MagiciteEffectSpeenUp::negative()
{
    ///> 这儿不需要做啥 交给timer来取消效果
}

