#include "MagiciteGameContact.h"

USING_NS_CC;

bool MagiciteGameContact::try_moveable_contact_with_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameObject* ground                  = trivialGround(objectA, objectB);
    MagiciteGameObject* object                  = nullptr;
    MagiciteGameLiving* living                  = nullptr;
    MagiciteGameMoveAbleLiving* moveableLiving  = nullptr;

    if (ground == nullptr) return false;
    object = (ground == objectA ? objectB : objectA);

    if (object->ObjType != MagiciteGameObject::T_Living) return false;
    living = reinterpret_cast<MagiciteGameLiving*>(object);

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

MagiciteGameMoveAbleLiving* MagiciteGameContact::trivialPlayer(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    if (objectA->ObjType == MagiciteGameObject::T_Living
        && reinterpret_cast<MagiciteGameLiving*>(objectA)->MoveAbleLiving == MagiciteGameLiving::MoveAbleType::MoveAbleLiving
        &&reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA)->_is_contraled == true)
    {
        return reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    }
    if (objectB->ObjType == MagiciteGameObject::Type::T_Living
        && reinterpret_cast<MagiciteGameLiving*>(objectB)->MoveAbleLiving == MagiciteGameLiving::MoveAbleType::MoveAbleLiving
        &&reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectB)->_is_contraled == true)
    {
        return reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectB);
    }
    return nullptr;
}

bool MagiciteGameContact::try_player_to_end(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* player = trivialPlayer(objectA, objectB);
    MagiciteGameObject* p_end = nullptr;
    MagiciteGameObject* object = nullptr;

    if (player == nullptr) return false;
    p_end = (player == objectA ? objectB : objectA);

    if (p_end->ObjType != MagiciteGameObject::T_End) return false;
    return true;
}

bool MagiciteGameContact::try_player_to_pitfall(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* player = trivialPlayer(objectA, objectB);
    MagiciteGamePitfall* pitfall = nullptr;
    MagiciteGameObject* object = nullptr;

    if (player == nullptr) return false;
    object = (player == objectA ? objectB : objectA);

    if (object->ObjType != MagiciteGameObject::T_Pitfall) return false;
    pitfall = reinterpret_cast<MagiciteGamePitfall*>(object);

    if (pitfall->getPitFallAvtive())
    {
        return true;
    }
    return false;
}

bool MagiciteGameContact::calc_player_and_enemy(MagiciteGameMoveAbleLiving* player, MagiciteGameLiving* enemy)
{
    Vec2 playerPos = player->getPosition();
    Vec2 enemyPos = enemy->getPosition();
    Size playergSize = player->getContentSize();
    Size enemySize = enemy->getContentSize();

    if (playerPos.x + playergSize.width / 2 > enemyPos.x - enemySize.width / 2
        && playerPos.x - playergSize.width / 2 < enemyPos.x + enemySize.width / 2)
    {
        if (playerPos.y - playergSize.height / 2 + -1 *(player->getBody()->GetLinearVelocity().y)+ 1
            >= enemyPos.y + enemySize.height / 2)
        {
            return true;
        }
    }
    return false;
}

bool MagiciteGameContact::is_all_living(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    if (objectA->ObjType == objectB->ObjType && objectA->ObjType == MagiciteGameObject::T_Living)
    {
        return true;
    }
    return false;
}

bool MagiciteGameContact::try_player_contact_with_enemy(MagiciteGameMoveAbleLiving* player, MagiciteGameLiving* enemy)
{
    if (enemy == nullptr || player == nullptr) return nullptr;

    return  calc_player_and_enemy(player, enemy);
}

void MagiciteGameContact::try_enemy_contact_with_enemy(MagiciteGameLiving* enemyA, MagiciteGameLiving* enemyB)
{
    try_to_change_living_direction(enemyA);
    try_to_change_living_direction(enemyB);
}

bool MagiciteGameContact::is_have_player(MagiciteGameLiving* livingA, MagiciteGameLiving* livingB)
{
    if (reinterpret_cast<MagiciteGameMoveAbleLiving*>(livingA)->_is_contraled
        || reinterpret_cast<MagiciteGameMoveAbleLiving*>(livingB)->_is_contraled)
    {
        return true;
    }
    return false;
}