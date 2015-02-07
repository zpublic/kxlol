#include "MagiciteGameContact.h"

USING_NS_CC;

bool MagiciteGameContact::try_moveable_contact_with_grond(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameObject* ground                  = trivialGround(objectA, objectB);
    MagiciteGameLiving* living                  = nullptr;
    MagiciteGameMoveAbleLiving* moveableLiving  = nullptr;
    if (ground == nullptr) return false;

    living = reinterpret_cast<MagiciteGameLiving*>(ground == objectA ? objectB : objectA);
    if (living->LivingMoveType != MagiciteGameLiving::MoveAbleLiving) return false;

    moveableLiving = reinterpret_cast<MagiciteGameMoveAbleLiving*>(living);
    if (is_moveable_on_ground(moveableLiving, ground))
    {
        if (is_moveable_above_ground(moveableLiving, ground))
        {
            moveableLiving->JumpOver();
        }
    }
    else
    {
        if (!moveableLiving->_is_contraled)
        {
            change_moveable_direction(moveableLiving);
        }
    }
    return true;
}

MagiciteGameObject* MagiciteGameContact::trivialGround(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    if (objectA->ObjType == MagiciteGameObject::Type::T_Ground) return objectA;
    if (objectB->ObjType == MagiciteGameObject::Type::T_Ground) return objectB;
    return nullptr;
}

void MagiciteGameContact::change_moveable_direction(MagiciteGameMoveAbleLiving* moveObj)
{
    if (moveObj->getDire() == MagiciteGameMoveAbleLiving::Direction::right)
    {
        moveObj->setDire(MagiciteGameMoveAbleLiving::Direction::left);
    }
    else
    {
        moveObj->setDire(MagiciteGameMoveAbleLiving::Direction::right);
    }
}

bool MagiciteGameContact::is_moveable_on_ground(MagiciteGameMoveAbleLiving* moveObj, MagiciteGameObject* ground)
{
    Vec2 objPos = moveObj->getPosition();
    Vec2 groundPos = ground->getPosition();
    Size objSize = moveObj->getContentSize();
    Size groundSize = ground->getContentSize();

    if (objPos.x + objSize.width / 2 > groundPos.x - groundSize.width / 2
        && objPos.x - objSize.width / 2 < groundPos.x + groundSize.width / 2)
    {
        return true;
    }
    return false;
}

bool MagiciteGameContact::is_moveable_above_ground(MagiciteGameMoveAbleLiving* moveObj, MagiciteGameObject* ground)
{
    if (moveObj->getPositionY() - moveObj->getContentSize().height / 2 
        >= ground->getPositionY() + ground->getContentSize().height / 2)
    {
        return true;
    }
    return false;
}

bool MagiciteGameContact::try_enemy_contact_with_living(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameLiving* enemy = trivialEnemy(objectA, objectB);
    MagiciteGameLiving* living = nullptr;
    if (enemy == nullptr) return false;

    living = reinterpret_cast<MagiciteGameLiving*>(enemy == objectA ? objectB : objectA);
    if (living->LivingMoveType == MagiciteGameLiving::MoveAbleLiving)
    {
        auto moveableLiving = reinterpret_cast<MagiciteGameMoveAbleLiving*>(living);
        if (moveableLiving->_is_contraled)
        {
            log("failed");
            return true;
        }
        else
        {
            change_moveable_direction(reinterpret_cast<MagiciteGameMoveAbleLiving*>(living));
            try_to_change_living_direction(enemy);
        }
    }
    else
    {
        if (enemy->LivingMoveType == MagiciteGameLiving::MoveAbleLiving)
        {
            change_moveable_direction(reinterpret_cast<MagiciteGameMoveAbleLiving*>(enemy));
        }
        return true;
    }
    return false;
}

MagiciteGameLiving* MagiciteGameContact::trivialEnemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    if (objectA->ObjType == MagiciteGameObject::T_Living)
    {
        auto living = reinterpret_cast<MagiciteGameLiving*>(objectA);
        if (living->LivingMoveType == MagiciteGameLiving::NormalLiving)
        {
            if (living->NormalLivingType == MagiciteGameLiving::Piranha)
            {
                return living;
            }
        }
        else
        {
            auto moveableLiving = reinterpret_cast<MagiciteGameMoveAbleLiving*>(living);
            if (moveableLiving->_is_contraled == false)
            {
                return moveableLiving;
            }
        }
    }
    if (objectB->ObjType == MagiciteGameObject::T_Living)
    {
        auto living = reinterpret_cast<MagiciteGameLiving*>(objectB);
        if (living->LivingMoveType == MagiciteGameLiving::NormalLiving)
        {
            if (living->NormalLivingType == MagiciteGameLiving::Piranha)
            {
                return living;
            }
        }
        else
        {
            auto moveableLiving = reinterpret_cast<MagiciteGameMoveAbleLiving*>(living);
            if (moveableLiving->_is_contraled == false)
            {
                return moveableLiving;
            }
        }
    }
    return nullptr;
}

void MagiciteGameContact::try_to_change_living_direction(MagiciteGameLiving* living)
{
    if (living->LivingMoveType == MagiciteGameLiving::MoveAbleLiving)
    {
        change_moveable_direction(reinterpret_cast<MagiciteGameMoveAbleLiving*>(living));
    }
}