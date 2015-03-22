#include "MagiciteGameAutoMoveAble.h"

void MagiciteGameAutoMoveAble::AutoMove()
{
    auto pos = getPos();
    if (_is_to_left)
    {
        if (pos.x < _pointA.x || fabs(pos.x - _pointA.x) < 0.000005)
        {
            setDire(MagiciteGameMoveAble::right);
        }
    }
    else
    {
        if (pos.x > _pointB.x || fabs(pos.x - _pointB.x) < 0.000005)
        {
            setDire(MagiciteGameMoveAble::left);
        }
    }
    Move(getDire());
}
