#include "MagiciteGameContact.h"

std::function<void(void)> MagiciteGameContact::_onWin = MagiciteGameContact::holders;
std::function<void(void)> MagiciteGameContact::_onOver = MagiciteGameContact::holders;

std::map<MagiciteGameContact::Contact_type, std::map<MagiciteGameContact::Contact_type, std::function<void(MagiciteGameObject*, MagiciteGameObject*)>>> MagiciteGameContact::on_contact;

USING_NS_CC;

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
    moveObj->Move(moveObj->getDire());
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

void MagiciteGameContact::try_to_change_living_direction(MagiciteGameLiving* living)
{
    if (living->LivingMoveType == MagiciteGameLiving::MoveAbleLiving)
    {
        change_moveable_direction(reinterpret_cast<MagiciteGameMoveAbleLiving*>(living));
    }
}

void MagiciteGameContact::resiger_contact()
{
    on_contact[Contact_type::enemy_type][Contact_type::ground_type] = std::bind(try_living_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::friend_type][Contact_type::ground_type] = std::bind(try_living_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::player_type][Contact_type::ground_type] = std::bind(try_living_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::enemy_type][Contact_type::ground_type] = std::bind(try_living_contact_with_ground, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::ammo_type][Contact_type::ground_type] = std::bind(try_ammo_contact_with_ground, std::placeholders::_1, std::placeholders::_2);


    on_contact[Contact_type::enemy_type][Contact_type::player_type] = std::bind(try_player_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Contact_type::pitfall_type][Contact_type::player_type] = std::bind(try_player_contact_with_pitfall, std::placeholders::_2, std::placeholders::_1);
    on_contact[Contact_type::ground_type][Contact_type::player_type] = std::bind(try_living_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Contact_type::end_type][Contact_type::player_type] = std::bind(try_player_contact_with_end, std::placeholders::_2, std::placeholders::_1);
    on_contact[Contact_type::edge_type][Contact_type::player_type] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);

    on_contact[Contact_type::enemy_type][Contact_type::friend_type] = std::bind(try_friend_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Contact_type::pitfall_type][Contact_type::friend_type] = std::bind(try_friend_contact_with_pitfall, std::placeholders::_2, std::placeholders::_1);
    on_contact[Contact_type::ground_type][Contact_type::friend_type] = std::bind(try_living_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Contact_type::edge_type][Contact_type::friend_type] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);

    on_contact[Contact_type::friend_type][Contact_type::pitfall_type] = std::bind(try_friend_contact_with_pitfall, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::player_type][Contact_type::pitfall_type] = std::bind(try_player_contact_with_pitfall, std::placeholders::_1, std::placeholders::_2);

    on_contact[Contact_type::friend_type][Contact_type::enemy_type] = std::bind(try_friend_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::player_type][Contact_type::enemy_type] = std::bind(try_player_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::ground_type][Contact_type::enemy_type] = std::bind(try_living_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Contact_type::enemy_type][Contact_type::enemy_type] = std::bind(try_enemy_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::ammo_type][Contact_type::enemy_type] = std::bind(try_ammo_contact_with_enemy, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::edge_type][Contact_type::enemy_type] = std::bind(try_living_contact_with_edge, std::placeholders::_2, std::placeholders::_1);


    on_contact[Contact_type::player_type][Contact_type::end_type] = std::bind(try_player_contact_with_end, std::placeholders::_1, std::placeholders::_2);

    on_contact[Contact_type::enemy_type][Contact_type::ammo_type] = std::bind(try_ammo_contact_with_enemy, std::placeholders::_2, std::placeholders::_1);
    on_contact[Contact_type::ground_type][Contact_type::ammo_type] = std::bind(try_ammo_contact_with_ground, std::placeholders::_2, std::placeholders::_1);
    on_contact[Contact_type::edge_type][Contact_type::ammo_type] = std::bind(try_ammo_contact_with_edge, std::placeholders::_2, std::placeholders::_1);

    on_contact[Contact_type::ammo_type][Contact_type::edge_type] = std::bind(try_ammo_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::player_type][Contact_type::edge_type] = std::bind(try_living_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::friend_type][Contact_type::edge_type] = std::bind(try_living_contact_with_edge, std::placeholders::_1, std::placeholders::_2);
    on_contact[Contact_type::enemy_type][Contact_type::edge_type] = std::bind(try_living_contact_with_edge, std::placeholders::_1, std::placeholders::_2);

}

void MagiciteGameContact::try_living_contact_with_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGameObject* ground = objectB;
    if (MagiciteGameContact::is_moveable_on_ground(living, ground))
    {
        if (MagiciteGameContact::is_moveable_above_ground(living, ground))
        {
            living->JumpOver();
        }
    }
    else
    {
        if (!living->_is_contraled)
        {
            MagiciteGameContact::change_moveable_direction(living);
        }
    }
}

void MagiciteGameContact::try_player_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* player = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGameLiving* enemy = reinterpret_cast<MagiciteGameLiving*>(objectB);

    Vec2 playerPos = player->getPosition();
    Vec2 enemyPos = enemy->getPosition();
    Size playergSize = player->getContentSize();
    Size enemySize = enemy->getContentSize();

    if (playerPos.x + playergSize.width / 2 > enemyPos.x - enemySize.width / 2
        && playerPos.x - playergSize.width / 2 < enemyPos.x + enemySize.width / 2)
    {
        if (playerPos.y - playergSize.height / 2 + -1 * (player->getBody()->GetLinearVelocity().y) + 1
            >= enemyPos.y + enemySize.height / 2)
        {
            enemy->attact();
            if (enemy->getHP() <= 0)
            {
                MagiciteGaemFactoryMethod::destroyEnemy(enemy);
            }
            player->JumpOver();
            player->Jump();
        }
        else
        {
            player->attact();
            if (player->getHP() <= 0)
            {
                onOver();
            }
        }
    }
}

void MagiciteGameContact::try_player_contact_with_pitfall(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* player = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGamePitfall* pitfall = reinterpret_cast<MagiciteGamePitfall*>(objectB);
    if (pitfall->getPitFallAvtive())
    {
        player->attact();
        if (player->getHP() <= 0)
        {
            onOver();
        }
    }
}

void MagiciteGameContact::try_friend_contact_with_pitfall(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGamePitfall* pitfall = reinterpret_cast<MagiciteGamePitfall*>(objectB);
    if (pitfall->getPitFallAvtive())
    {
        living->attact();
        if (living->getHP() <= 0)
        {
            MagiciteGaemFactoryMethod::destroyFriend(living);
        }
        if (pitfall->PiffallType == MagiciteGamePitfall::Spine)
        {
            MagiciteGaemFactoryMethod::destroyPitfall(pitfall);
        }
    }
}

void MagiciteGameContact::try_friend_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    MagiciteGameMoveAbleLiving* living = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    MagiciteGameMoveAbleLiving* enemy = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectB);

    MagiciteGameContact::change_moveable_direction(living);
    living->attact();
    if (living->getHP() <= 0)
    {
        MagiciteGaemFactoryMethod::destroyFriend(living);
    }
    MagiciteGameContact::change_moveable_direction(enemy);
    enemy->attact();
    if (enemy->getHP() <= 0)
    {
        MagiciteGaemFactoryMethod::destroyEnemy(enemy);
    }
}

void MagiciteGameContact::try_enemy_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto livingA = reinterpret_cast<MagiciteGameLiving*>(objectA);
    auto livingB = reinterpret_cast<MagiciteGameLiving*>(objectB);
    MagiciteGameContact::try_to_change_living_direction(livingA);
    MagiciteGameContact::try_to_change_living_direction(livingB);
}

void MagiciteGameContact::try_player_contact_with_end(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    onWin();
}

void MagiciteGameContact::try_ammo_contact_with_enemy(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto ammo = reinterpret_cast<MagiciteGameAmmo*>(objectA);
    auto enemy = reinterpret_cast<MagiciteGameLiving*>(objectB);
    ammo->Dead();
    enemy->attact();
    if (enemy->getHP() <= 0)
    {
        MagiciteGaemFactoryMethod::destroyEnemy(enemy);
    }
}

void MagiciteGameContact::try_ammo_contact_with_ground(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto ammo = reinterpret_cast<MagiciteGameAmmo*>(objectA);
    ammo->Dead();
}

void MagiciteGameContact::try_ammo_contact_with_edge(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    objectA->Dead();
}

void MagiciteGameContact::try_living_contact_with_edge(MagiciteGameObject* objectA, MagiciteGameObject* objectB)
{
    auto moveLiving = reinterpret_cast<MagiciteGameMoveAbleLiving*>(objectA);
    if (!moveLiving->_is_contraled)
    {
        MagiciteGameContact::try_to_change_living_direction(moveLiving);
    }
}

void MagiciteGameContact::holders()
{

}

MagiciteGameContact::Contact_type MagiciteGameContact::trivial_contact_type(MagiciteGameObject* object)
{
    if (object == nullptr) return edge_type;
    if (object->ObjType == MagiciteGameObject::T_Ammo) return Contact_type::ammo_type;
    if (object->ObjType == MagiciteGameObject::T_Pitfall) return Contact_type::pitfall_type;
    if (object->ObjType == MagiciteGameObject::T_Ground) return Contact_type::ground_type;
    if (object->ObjType == MagiciteGameObject::T_End) return Contact_type::end_type;
    if (object->ObjType == MagiciteGameObject::T_Living)
    {
        auto living = reinterpret_cast<MagiciteGameLiving*>(object);
        if (living->LivingMoveType == MagiciteGameLiving::MoveAbleLiving)
        {
            auto moveable = reinterpret_cast<MagiciteGameMoveAbleLiving*>(living);
            if (moveable->_is_contraled)
            {
                return Contact_type::player_type;
            }
            else
            {
                if (moveable->_is_friend)
                {
                    return Contact_type::friend_type;
                }
                else
                {
                    return Contact_type::enemy_type;
                }
            }
        }
        else
        {
            return Contact_type::enemy_type;
        }
    }
    return Contact_type::unknow_type;
}

bool MagiciteGameContact::is_in_types(MagiciteGameContact::Contact_type type)
{
    if (type == Contact_type::end_type 
        || type == Contact_type::enemy_type 
        || type == Contact_type::friend_type
        || type == Contact_type::ground_type 
        || type == Contact_type::pitfall_type 
        || type == Contact_type::player_type
        || type == Contact_type::ammo_type
        || type == Contact_type::edge_type)
    {
        return true;
    }
    return false;
}

void MagiciteGameContact::onWin()
{
    _onWin();
}

void MagiciteGameContact::onOver()
{
    _onOver();
}